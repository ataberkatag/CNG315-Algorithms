This assignment aims to help you practice the heap data structure and heap sort algorithm. 
Your main task in this assignment is to develop a simple leaderboard system using C programming language.


Overview:
Every leaderboard needs a couple of sorting features to help you see which participant is the leader when it comes to a certain aspect. 
Having the most wins does not mean the best win rate, and the expectation to win placed upon each opponent plays a major role, especially in the betting department. 
Since heap sort has been the highlight of the week, the focus will mostly be on implementing it to sort our leaderboard the way the user desires.

Normally, we are using command line to execute .txt files and choosing the option but for simplicity i put the names and option inside the document.
If you make the necessary changes you can easily work with the terminal.

Example battle.txt:
  battle1 XQ3 Ashya XQ3
  battle2 XQ3 Ashya Ashya
  battle3 Alphi Cera2 Alphi
  battle4 Alphi XQ3 Alphi
  battle5 Crow Cera2 Crow
  battle6 Crow Alphi Alphi
  battle7 Cera2 Gingi Cera2
  battle8 Ashya Alphi Ashya
  battle9 Gingi Crow Crow
  battle10 Gingi Ashya Ashya
  
Example champion.txt:
  XQ3 1
  Ashya 0.25
  Gingi 0.33
  Cera2 0.5
  Crow 0.33
  Alphi 0.75
  
Options:
  1. actual win rate
  2. expected win rate
  3. expectation skew

At line 228,there is a "argv[1] = "1"; " if you wanna try other options change it.
