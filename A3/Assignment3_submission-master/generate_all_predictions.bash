DM=`ls query` #DMEGER origianl file
dataList=`ls data`

make # create the executable if not created already

./movie_recommender query/$DM data/*

mv query/$DM data/

for item in $dataList
do
    mv data/$item query/
    # echo $item
    ./movie_recommender query/$item data/*
    mv query/$item data/
done

mv data/$DM query