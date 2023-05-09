# C WEB SERVER
* Author: Nguyen Phuc Dang
* Reference: 
    * [I made a web server In C like a true sigma](https://www.youtube.com/watch?v=cEH_ipqHbUw)
    * [Data Structure and Algorithms - Hash Table](https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm)
    

## Abstract
Thanks to [Imran Rahman](https://www.youtube.com/@imraninfrarote), I have implement a basic Web Server by C using Unix Socket API and implemented hash table based on hash function for Routing:
```
unsigned long hash(char* key){
    unsigned long i = 0;
    for(int j = 0; key[j]; j++){
        i += key[j] << 5;
    }
    return i % CAPACITY;
}
```

## Compile these files
Using ```make``` to compile these files and ```make clean``` to clean all the output files.


## Result
### First look
![Testing program 1](/img/update1/1.png "index Page")
![Testing program 2](/img/update1/2.png "about Page")

I will implement more ...

