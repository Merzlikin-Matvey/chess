#!/bin/bash

repos=($(jq -r '.dependencies[]' dependencies.json))

for repo in "${repos[@]}"; do
    IFS='/' read -r -a array <<< "$repo"
    author_name=${array[0]}
    repo_name=${array[1]}
    branch_name=${array[2]}
    file_name=${array[-1]}

    path=../include/$repo_name

    if [ -d $path ]; then
        rm -rf $path
    fi

    mkdir -p $path
    curl -LO https://raw.githubusercontent.com/$repo;
    mv $file_name $path

    if [ $? -eq 0 ]; then
        echo "Установка $repo_name прошла успешно"
    else
        echo "Ошибка при установке $repo_name"
        exit 1
    fi
done
