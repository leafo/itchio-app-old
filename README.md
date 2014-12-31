# itch.io app

**This project is in very early development!**

The itch.io app is a cross-platform client for the [itch.io][1] marketplace. It is built with the
Qt 5 framework and is currently available for Windows, Linux and OS X.

## Building the client

Firstly, clone the project
```bash
$ git clone https://github.com/leafo/itchio-app.git
```

To compile and run the project, you can open the `itchio.pro` file from [Qt Creator][2] and click run.
The build procedure can also be performed from the command line via the following commands:
```bash
$ cd itchio-app
$ make
$ ./build/itchio
```

For more information on the available `make` targets, please read the provided help page
```bash
$ make help
```


## Coding style

`astyle` is used to format the codebase. The 1TBS preset is used. To format all
source files run:
```bash
$ make format
```


WIP Dev Log

![](http://leafo.net/shotsnb/2014-12-17_15-19-25.png)

![](http://leafo.net/shotsnb/2014-12-17_12-08-25.png)

[1]: https://itch.io "itch.io indie games marketplace"
[2]: http://qt-project.org/wiki/Category:Tools::QtCreator "Qt Creator info page"


## License

Licensed under MIT License, see `LICENSE` for details.
