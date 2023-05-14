# Assigment False Sharing

### Complie Code for Pthreads with Flase Sharing (Version 1)
```gcc -Wall -O0 -o gregoryLeibnizV1  gregoryLeibnizV1.c```

##### Run Compiled Code
```.\gregoryLeibnizV1.exe iterations``` 

### Complie Code for Pthreads with Flase Sharing (Version 2)
```gcc -Wall -O0 -o gregoryLeibnizV2  gregoryLeibnizV2.c -pthread```

##### Run Compiled Code
```.\gregoryLeibnizV2.exe iterations num_threads``` 

### Complie Code for Pthreads without Flase Sharing (Version 3)
```gcc -Wall -O0 -o gregoryLeibnizV3  gregoryLeibnizV3.c -pthread```

##### Run Compiled Code
```.\gregoryLeibnizV3.exe iterations num_threads```

### Automate with Scripting
#### Windows
```.\script-windows.bat```

#### Linux
```chmod +x script-linux.sh```

```./script-linux.sh```
