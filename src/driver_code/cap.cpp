#include <string>
#include <iostream>
std::string generateCAPMessage(float tempMean, float tempSD, float humidityMean, float humiditySD, float pressureMean, float pressureSD, float lightMean, float lightSD){
    const char *CAP_TEMPLATE =
        "<?xml version = \"1.0\" encoding = \"UTF-8\"?>"
        "<alert xmlns = \"urn:oasis:names:tc:emergency:cap:1.2\">"
        " <sender>MICROCONTROLLER</sender>"

        " <info>"
        " <event>SENSOR_DATA</event>"

        " <parameter>"
        " <valueName>MEAN_TEMPERATURE</valueName>"
        " <value>" + std::to_string(tempMean)+ "</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>TEMPERATURE_SD</valueName>"
        " <value>"+ std::to_string(tempSD)+"</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>MEAN_HUMIDITY</valueName>"
        " <value>"+ std::to_string(humidityMean)+"</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>HUMIDITY_SD</valueName>"
        " <value>"+ std::to_string(humiditySD)+"</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>MEAN_PRESSURE</valueName>"
        " <value>"+ std::to_string(pressureMean)+"</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>PRESSURE_SD</valueName>"
        " <value>"+ std::to_string(pressureSD)+"</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>MEAN_LIGHT</valueName>"
        " <value>"+ std::to_string(lightMean)+"</value>"
        " </parameter>"

        " <parameter>"
        " <valueName>LIGHT_SD</valueName>"
        " <value>"+ std::to_string(lightSD)+"</value>"
        " </parameter>"

        " </info>"
        "</alert>";

    snprintf(tempMean, tempSD, humidityMean, humiditySD, pressureMean, pressureSD, lightMean, lightSD);
}
