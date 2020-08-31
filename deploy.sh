cp ./build/bbc-microbit-classic-gcc/source/rovercode-gigglebot-mbed-combined.hex ./rovercode.hex
aws s3 sync \
    --metadata BuildNumber=${GITHUB_RUN_ID} \
    --acl public-read \
    --content-disposition attachment \
    build/ s3://rovercode-gigglebot-mbed/$1/
