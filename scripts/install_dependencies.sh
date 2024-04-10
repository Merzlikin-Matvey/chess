#!/bin/bash

# If dependencies.json file does not exist, exit with error
if [ ! -f ../dependencies.json ]; then
    echo "File dependencies.json does not exist"
    exit 1
fi

# Read dependencies.json file and get all dependencies
repos=($(jq -r '.dependencies[]' ../dependencies.json))

for repo in "${repos[@]}"; do
    IFS='/' read -r -a array <<< "$repo"
    author_name=${array[0]}
    repo_name=${array[1]}
    branch_name=${array[2]}
    file_name=${array[-1]}

    path=../dependencies/$repo_name

    if [ -d $path ]; then
        rm -rf $path
    fi

    # Download the file from the repository
    mkdir -p $path
    curl -LO https://raw.githubusercontent.com/$repo;
    mv $file_name $path

    if [ $? -eq 0 ]; then
        echo "$repo_name installed successfully"
    else
        echo "Failed to install $repo_name"
        exit 1
    fi
done
