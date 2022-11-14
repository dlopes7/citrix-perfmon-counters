# Example powershell -f generate_xml.ps1 Win32_PerfRawData_PerfOS_Processor
$wmi_class = $args[0]

if ($wmi_class -notmatch "^Win32_PerfRawData_") {
    Write-Host "WMI class must start with Win32_PerfRawData_"
    exit
}

Write-Host "Generating XML for $wmi_class"

$split_values = $wmi_class -split "_"
$provider_name = $split_values[2]
$counter_set_name = $split_values[3]

$base_xml_template = @"
<?xml version="1.0"?>
<instrumentationManifest
    xmlns="http://schemas.microsoft.com/win/2004/08/events"
    xmlns:win="https://manifests.microsoft.com/win/2004/08/windows/events"
    xmlns:xs="https://www.w3.org/2001/XMLSchema"
    >

    <instrumentation>

        <counters
        xmlns="http://schemas.microsoft.com/win/2005/12/counters"
        schemaVersion="2.0">

            <provider
                applicationIdentity="counter_generator.exe"
                symbol="<provider_name>"
                providerName="<provider_name>"
                providerGuid="{<provider_guid>}">

                <counterSet
                    guid="{<counter_set_guid>}"
                    uri="Custom.PerfCounters.<counter_set_name>"
                    symbol="<counter_set_name>"
                    name="<counter_set_name>"
                    nameID="100"
                    description="<counter_set_name> Counters"
                    descriptionID="102"
                    instances="multiple">

                        <counters>
                </counterSet>

            </provider>
        </counters>
    </instrumentation>
</instrumentationManifest>
"@

# Replace the provider name and guid
$final_xml = $base_xml_template -replace "<provider_name>", $provider_name
$final_xml = $final_xml -replace "<provider_guid>", [guid]::NewGuid()

# Replace the counter set name and guid
$final_xml = $final_xml -replace "<counter_set_name>", $counter_set_name
$final_xml = $final_xml -replace "<counter_set_guid>", [guid]::NewGuid()

Write-Host "Capturing properties for Provider '$provider_name' and Counter Set '$counter_set_name'"

# Get all properties that have CounterType in the Qualifiers
$properties = (Get-CimClass -ClassName $wmi_class).CimClassProperties | Where-Object { $_.Qualifiers.Name -contains "CounterType" }

$counter_template = @"
<counter
                            id="<counter_id>"
                            uri="Custom.PerfCounters.<counter_set_name>.<counter_name>"
                            symbol="<counter_name>"
                            name="<counter_display_name>"
                            nameID="<name_id>"
                            description="The value for <counter_display_name>"
                            descriptionID="<description_id>"
                            type="perf_counter_rawcount"
                            detailLevel="standard">

                            <counterAttributes>
                                <counterAttribute name="reference"/>
                            </counterAttributes>
                        </counter>

                        <counters>
"@

$counter_id = 1
$name_id = 104

foreach ($property in $properties) {
    $displayName = $property.Qualifiers["DisplayName"].Value

    # Only add counters where displayName is not null
    if ($displayName) {
        Write-Host "Adding counter '$($property)'"
        $counter_name = $property.Name
        $counter_xml = $counter_template -replace "<counter_id>", $counter_id
        $counter_xml = $counter_xml -replace "<counter_name>", $counter_name
        $counter_xml = $counter_xml -replace "<counter_display_name>", $property.Qualifiers["DisplayName"].Value
        $counter_xml = $counter_xml -replace "<name_id>", $name_id
        $counter_xml = $counter_xml -replace "<description_id>", ($name_id + 2)
        $counter_xml = $counter_xml -replace "<counter_set_name>", $counter_set_name

        $final_xml = $final_xml -replace "<counters>", $counter_xml

        $counter_id++
        $name_id = $name_id + 4
    }
}

$final_xml = $final_xml -replace "<counters>", ""

$final_xml | Out-File -FilePath "$provider_name.xml" -Encoding UTF8

Write-Host "Generated XML file '$provider_name.xml'"