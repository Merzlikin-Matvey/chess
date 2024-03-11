#!/bin/bash

# Список репозиториев для клонирования
# Формат: "author-name/repo-name/branch-name"
repos=(
    "nlohmann/json/master"
    "Merzlikin-Matvey/Base-converter/main"
)

if ! command -v unzip &> /dev/null
then
    echo "Установка unzip"
    sudo apt-get install unzip
fi

for repo in "${repos[@]}"; do
    IFS='/' read -r -a array <<< "$repo"
    author_name="${array[0]}"
    repo_name="${array[1]}"
    branch_name="${array[2]}"

    dir_path="dependencies/$author_name/$repo_name"

    mkdir -p $dir_path
    curl -L https://github.com/$author_name/$repo_name/archive/refs/heads/$branch_name.zip --output $dir_path/$branch_name.zip
    unzip $dir_path/$branch_name.zip -d $dir_path
    rm $dir_path/$branch_name.zip
done