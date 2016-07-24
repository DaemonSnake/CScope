# CSope
The implementation of scope(exit) from Dlang in C using gcc extensions.</br>

<h3>Examples</h3>

```D
void fill_file(const char *name)
{
   int fd = -1;
   
   if ((fd = open(name, ...)) == -1)
     return ;
   scope(exit) close(fd);
   ...
   if (write(fd, "something", 9) != 9)
      return ;
   ...
   return ;
}
```

<h3>Issue with current implementation</h3>
The only 'real' issue with this implementation is that you cannot use scope(exit)</br>
inside of a non-brackets surrounded block of code.</br>
This is clearly not a major issue as such a construct would be the equivalent of not using scope(exit).</br>
Here is an example that wont compile.</br>

```D
{
   if (something())
      scope(exit) { //This line will cause a compile error has the if statement in which it's located has no brackets
        printf("Will No compile\n");
      }
      
   if (something())
   {
     scope(exit) { //No problem here
        printf("Will compile\n");
     }
   }
}
```

<h3>More infomation on Scope guard statments</h3>
for more infomation on this idea I recommend this conference of Andrei Alexandrescu who's the co-creator of the D language</br>
<a href="https://www.youtube.com/watch?v=WjTrfoiB0MQ">CppCon 2015 "Declarative Control Flow</a>
