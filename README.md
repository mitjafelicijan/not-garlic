# Check top 1 million websites for Onion header link presence

If a website has an Onion header link, it means that the website is also available on the Tor network. This program checks the top 1 million websites for the presence of an Onion header link.

This program is written in C and uses libcurl to make HTTP requests. It is a single file program, so it is easy to compile and run.

Upon running the program, it will check the top 1 million websites from `top-1m.csv` file. It will then output the results to a file called `success.txt`.

![Cooking](https://user-images.githubusercontent.com/296714/210117490-57980824-42c8-46ba-a7d2-21656879d3d9.png)

## Usage


```sh
make

./garlic
```
