
count() { echo $#; }

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
index=0

declare -a fileList

find . -maxdepth 1 -type f  -print0 | while IFS= read -r -d $'\0' file; do
	PUZZLE_NAME="$OUTPUT_FILE.$index"
	echo "Index $index"
	fileList[$index]="$PUZZLE_NAME"
	echo "File: ${fileList[$index]}"
	genxword "$file" --output $PUZZLE_NAME s --auto
	index=$((index+1))
done

echo "x:$x";

echo "making json"
echo "{'baseName': '$OUTPUT_FILE'}" > description.json
echo "]}"

echo  ${fileList[*]}

popd

