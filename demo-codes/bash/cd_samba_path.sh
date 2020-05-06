#!/bin/bash
path=$1
new_path=${path#/*/}
new_path="/Volumes/$new_path"
echo $new_path
cd $new_path
