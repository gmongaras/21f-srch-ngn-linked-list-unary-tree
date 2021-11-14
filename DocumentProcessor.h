#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H


#include <string>
#include <filesystem>
#include <experimental/filesystem>


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/pointer.h"
#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <time.h>

namespace fs = std::experimental::filesystem;


class DocumentProcessor {
private:
    ;



public:
    /**
     * processDocuments Method
     * Accepts a directory name to parse .json documents from
     * @param directory The name of the directory to parse files from
     * @return The stored index object containing the information from
     *         the parsed datafiles
     */
    void processDocuments(const std::string& directory);
};





/****************************
 **    processDocuments    **
 ***************************/
void DocumentProcessor::processDocuments(const std::string& directory) {
    time_t timer;
    struct tm y2k = {0};
    double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    double original = time(&timer);  /* get current time; same as: timer = time(NULL)  */






    char* readBuffer = new char[65536]; // The buffer
    FILE* filePointer;

    // Iterate over all documents in the directory
    for (auto& entry : fs::recursive_directory_iterator(directory)) {
        //std::cout << entry.path().c_str() << std::endl;
        // Open the file if it's not a directory
        if (fs::is_directory(entry) == true) {
            continue;
        }

        // Open the file for reading
        filePointer = fopen(entry.path().c_str(), "rb");

        // If the file is not opened, skip it
        if (filePointer == nullptr) {
            continue;
        }

        // Read the JSON from the file into the document
        rapidjson::FileReadStream* inputStream = new rapidjson::FileReadStream(filePointer, readBuffer, sizeof(readBuffer));
        rapidjson::Document *doc = new rapidjson::Document;
        doc->ParseStream(*inputStream);

        // Get the text from the document
        rapidjson::Value& data = (*doc)["text"];


        // clean adn throw in tree



        // Reset the pointers and free the memory
        doc->RemoveAllMembers();
        delete doc;
        delete inputStream;
        fclose(filePointer);
        //delete filePointer;
        //memset(readBuffer, 0, sizeof(readBuffer));



//        //
//        // Variable to hold each line in the file
//        char* JSON = new char[10000];
//
//        // Open the file if it's not a directory
//        if (fs::is_directory(entry) == true) {
//            continue;
//        }
//        //file.open(entry.path());
//        std::ifstream file(entry.path(), std::ios_base::in); // the in flag is optional
//
////        // If the file is open, read the file
////        if (file.is_open()) {
////            // Get the JSON data
////            file.getline(JSON, 10000, '\n');
////
////            // Parse the JSON
////            rapidjson::Document d;
////            d.Parse(JSON);
////        }
////        // If the file is not open, throw an error
////        else {
////            throw std::runtime_error("File not open");
////        }
//
//        // Close the file
//        file.close();
//        fclose(fp);
    }


    std::cout << "Time: " << time(&timer)-original << " :( || :) " << std::endl;

    // Free the memory used to read the files
    delete readBuffer;
}



#endif // INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H