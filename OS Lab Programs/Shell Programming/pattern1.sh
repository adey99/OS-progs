echo "Can you see the following:"

for (( k=1; k<=5; k++ ))
do
    for (( l=1; l<=k;  l++ ))
    do
     echo -n "$k"
    done
    echo ""
done
