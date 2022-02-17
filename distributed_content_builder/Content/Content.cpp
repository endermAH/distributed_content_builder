//
// Created by Евгений Курятов on 17.02.2022.
//

#include <string>
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "Content.hpp"
#include "Task.hpp"
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>

namespace fs = std::filesystem;

std::vector<ITask*> Content::GetTasks(){

    // TODO: Split for different tasks

    std::vector<ITask*> task_list_;
    std::string path = content_path_;

    logger_->LogDebug("List of textures to build: ");
    for (const auto & entry : fs::directory_iterator(path))
        if (entry.path().extension() == ".json") {
            rapidjson::Document json_data;
            std::ifstream json_file(entry.path());
            rapidjson::IStreamWrapper isw { json_file };
            std::string content = "";
            std::string file_string;

            json_data.ParseStream(isw);
            logger_->LogDebug(entry.path());
            logger_->LogDebug(json_data["file"].GetString());

            std::string path_to_file = entry.path().parent_path().string() + "/" + json_data["file"].GetString();
            std::string path_to_compressed = entry.path().parent_path().string() + "/ready/" + json_data["file"].GetString();
            std::string params = path_to_file + " " + path_to_compressed;

            task_list_.push_back(new Task(json_data["executor"].GetString(), params));
        }
    return task_list_;
}