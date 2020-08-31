aws s3 sync \
    --metadata BuildNumber=${GITHUB_RUN_ID} \
    --acl public-read \
    --content-disposition attachment \
    built/ s3://rovercode-gigglebot-mbed/$1/
