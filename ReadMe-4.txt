This assignment aims to help you practice string processing and string matching. 
Your main task in this assignment is to develop another simple scanpath analyser using C programming language.

Overview
Autism Spectrum Disorder (ASD) is a neurodevelopmental disorder characterised by differences in communication and social interaction [1, 2]. 
Recent research studies have analysed the eye movements of people with and without autism recorded while interacting with web pages, 
and have found that people with autism tend to have different processing strategies in comparison with people without autism when they interact with web pages [1, 2].
Eye tracking is the process of recording the eye movements of people to understand where they look at, called fixations, 
and how long these fixations last. The series of their fixations represent their scanpaths. Scanpaths are usually analysed based on the areas of interest (AOIs) 
of visual stimuli, especially which AOIs are frequently used and in which order. 

Example data:
  peoplewithautism.txt:
    6547382712384758123
    3547712364687
    
  peoplewithoutautism:
    847364537292
    9374638473682
    8162537252

Expected output:
  Enter the file name for people with autism: peoplewithautism.txt
  Enter the file name for people without autism: peoplewithoutautism.txt 
  Enter the pattern: 123
Detected patterns for people with autism:
1. 65473827[123]84758[123]
2. 35477[123]64687
3 patterns detected in 2 scanpaths
The most frequent AOI before the pattern is/are 7
Detected patterns for people without autism: 
None
