Part 1:
    1. I am confirming the birthday paradox. The paradox is saying that when we have a room of people we will find two people with the same birthday 50.7% of the time after going through 23 people or less. This was demonstrated in class.

    2. My code can be found in bdayTest.cpp. In my code I have an outer for loop that repeats the test 1000 times, as recommended in the problem outline. Inside that for loop I initialize my hashtable of size 365. Then I have a while loop that will stop once the first probe occurs OR when the table is resized (load factor >= 0.5). Inside this while loop I first generate a random string of length 28 to input into my hashtable. I then add that string to my hashtable and increment n (objects inserted). Once I break from this while loop I have an if statement checking if n is <= 23 and another checking for the else case. Inside these if statements I increment variables resultOne and resultTwo which are used to find the percentages.

    3. I did 12 tests on my code and then averaged all of the results and found that resultOne occurred 50.7% of the time and resultTwo occurred 49.2% of the time. This can be recreating by running the code some amount of times (x) and then adding all of the resultOnes together and then dividing them by (x*100) and them repeating for resulttwo.

    My Results:

    Result One: 50.7%
    Result One: 50.2%
    Result One: 52.4%
    Result One: 51.8%
    Result One: 50.8%
    Result One: 51%
    Result One: 50.6%
    Result One: 51.5%
    Result One: 49.3%
    Result One: 47.2%
    Result One: 51.9%
    Result One: 51.7%

    Result Two: 47.6%
    Result Two: 49.8%
    Result Two: 48.2%
    Result Two: 49.3%
    Result Two: 49%
    Result Two: 49.2%
    Result Two: 49.4%
    Result Two: 48.5%
    Result Two: 50.7%
    Result Two: 52.8%
    Result Two: 48.1%
    Result Two: 48.3%

Part 2:
    1. I am confirming the probe rate for problem 2. The problem is asking to confirm that when we insert into a hashtable that is half full, the average probe will be 1. When we do the same for a hashtable that is 1/4 full the average probe rate will be 1/3 (or 2n/3). It also says that the max probe of each test will be on the order of logn.

    2. My code can be found in main.cpp. In my code I have an outer for loop that repeats the test 1000 times. I then have another loop that adds m items to my hashtable. Inside that loop I have another loop to initialize random strings of length 28, same as my birthday paradox code. I then add that string to my hashtable and if the loading factor is around 0.5 (between 0.5 and 0.45) I push back into a vector holding all the probe values for when my table is half full. I repeat this for when my table is 1/4 full (between 0.25 and 0.2).I then check if the probe is the max. Outside of this loop I output the maximum probes and their corresponding number of inserts. I then average the 1/2 full probes and 1/4 full probes and output their averages.

    3. I did 6 tests on my code and then averaged all of the results and found that the average for 1/2 full probes is 1.07729 and the average for 1/4 full probes is 0.28958. The maximum probes are near to being on the order of logn, on average they are very close but some aren't exactly logn. Below I only show 4 of the max probe values as a sample for each iteration.

    My Results:
        MaxProbe: 8  n:1585
        MaxProbe: 10  n:2894
        MaxProbe: 8  n:1574
        MaxProbe: 11  n:2534
        1.025 probes on average when 1/2 full
        0.26875 probes on average when 1/4 full
        ------------------------------------------

        MaxProbe: 9  n:1492
        MaxProbe: 11  n:3061
        MaxProbe: 11  n:3119
        MaxProbe: 10  n:1502
        0.9875 probes on average when 1/2 full
        0.35625 probes on average when 1/4 full
        ------------------------------------------

        MaxProbe: 9  n:1377
        MaxProbe: 12  n:3156
        MaxProbe: 7  n:1227
        MaxProbe: 11  n:1508
        0.98125 probes on average when 1/2 full
        0.26875 probes on average when 1/4 full
        ------------------------------------------

        MaxProbe: 12  n:1343
        MaxProbe: 8  n:1515
        MaxProbe: 13  n:3118
        MaxProbe: 8  n:1480
        1.09375 probes on average when 1/2 full
        0.3 probes on average when 1/4 full
        ------------------------------------------

        MaxProbe: 10  n:2917
        MaxProbe: 14  n:3147
        MaxProbe: 10  n:3185
        MaxProbe: 8  n:2904
        1.225 probes on average when 1/2 full
        0.30625 probes on average when 1/4 full
        ------------------------------------------

        MaxProbe: 14  n:3188
        MaxProbe: 9  n:1572
        MaxProbe: 8  n:2967
        MaxProbe: 13  n:2580
        1.15 probes on average when 1/2 full
        0.2375 probes on average when 1/4 full
        ------------------------------------------