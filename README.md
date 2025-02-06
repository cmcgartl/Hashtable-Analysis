## Problem 2

Answer Problem 2 here, **DO NOT FORGET!**

I began by confirming the birthday paradox. To do this, I created a file called birthday.cpp in which I create a hash table of size 365, with the debug boolean set to false to ensure random data. I then created a main function that creates 1 million random strings of letters of length 10, and stored them in a vector. I then added a new selection of these generated random strings into the empty hashtable until a collision occured, and tracked the number of inserts it required before a collision occured. My program repeats this 1000 times, and records the total number of instances where it took 23 or less inserts to find a collision, and the total where it took more than 23. I then found the average, and repeated this process 10 times to find the overall average for each. From my data, I found that it took 23 or less inserts 49.88 percent of the time, and more than 23 inserts 50.12 percent of the time, thus confirming the birthday paradox.

I then created a new file called averageProbe.cpp, in which I made a program that creates a collection of 1 million random strings of length 10 in the same way as in Birthday.cpp. I then created a nested for loop that would do a set number of inserts into an empty hashtable 1000 times, and recorded the total number of probes for each insert, the highest probe count of any 1 insert, and the averages over the 1000 trials. I then went in and changed the et number of inserts, testing for 10, 50, 100, 500, and 1000 inserts into an empty hashtable of size 11. I found that the average number of probes for each number of inserts respectively was 1.128, 26.087, 59.231, 308.692, 629.288. The expected value for these averages was slightly under 2n/3 probes, which for the cases of 10 and 20 inserts the probe average was lower than expected, but began to approach the expected 2n/3 as the number of inserts increased. The average max number of inserts respectively was: 4.6, 10.6, 13.4, 16.16, 17.2 which was over the logn estimate.