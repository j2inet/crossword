
INPUT_FILE=$1
OUTPUT_FILE=$2

mkdir working
mkdir working/clean

rm working/*
rm working/clean/*

echo $INPUT_FILE
ssconvert $INPUT_FILE working/$OUTPUT_FILE -S
pushd working

pwd;
find . -maxdepth 1 -type f  -print0 | while IFS= read -r -d $'\0' file; do
    ../clean-puzzle/clean-puzzle "$file" >> "clean/$file.clean"  
done

cd clean
find . -maxdepth 1 -type f  -print0 | while IFS= read -r -d $'\0' file; do
    genxword "$file" --output $OUTPUT_FILE s --auto
done



popd

