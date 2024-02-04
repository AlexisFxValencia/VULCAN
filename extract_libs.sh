#!/bin/bash

cd lib
zip_file="external_libraries.zip"
extracted_folder_SFML="SFML-2.5.1-linux-gcc-64-bit"
extracted_folder_tgui="TGUI-0.9.5"

# Check if both the extracted folders exist
if [ -d "$extracted_folder_SFML" ] && [ -d "$extracted_folder_tgui" ]; then
    echo "Both folders $extracted_folder_SFML and $extracted_folder_tgui already exist. No action needed."
else
    # Check if the ZIP file exists
    if [ -e "$zip_file" ]; then
        unzip "$zip_file" 
        echo "Extraction completed successfully."
    else
        echo "The file $zip_file does not exist in the current directory."
    fi
fi
cd ..
