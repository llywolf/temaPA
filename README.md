# LAN Party Program

This program is designed to manage a LAN party event. It performs various tasks related to team management and competition results. The program takes input from files and produces output based on the specified tasks.

## Features

The LAN Party program includes the following features:

1. **Task 1**: Display the list of teams participating in the LAN party.
2. **Task 2**: Remove surplus teams if the team number isn't eligible for the tournament.
3. **Task 3**: Simulate rounds of competition until a final winner is determined.
4. **Task 4**: Generate a leaderboard of the top 8 teams.
5. **Task 5**: Build an AVL tree with the teams from the second level.

## Usage

To use the LAN Party program, follow these steps:

1. Compile the program from the command line with `make`, using the associated makefile.
2. Execute the compiled program from the command line, providing the necessary command line arguments:

```shell
./lanParty c.in d.in r.out
```

- `c.in`: Specifies the file containing configuration settings for the program.
- `d.in`: Specifies the file containing input data for the LAN party.
- `r.out`: Specifies the file where the program will write the results.

To test all the tasks, from the command line write 
```shell
./checker.sh
```

## Configuration File

The program requires a configuration file (`c.in`) to specify which tasks to perform. The format of the configuration file should be as follows:
```shell
<task1> <task2> <task3> <task4> <task5>
```

Each task should be represented by a `0` or `1`:

- `0`: The task is disabled.
- `1`: The task is enabled.

For example, to enable Task 1 and Task 3 while disabling the others, the configuration file should contain:
```shell
1 0 1 0 0
```

Make sure to provide the correct path to the configuration file when executing the program.

## Input File

The LAN Party program expects an input file (`d.in`) containing the necessary data for the LAN party. The format of the input file should adhere to the following guidelines:

1. The first line should contain the number of teams participating in the LAN party.
2. Subsequent lines should provide information about each team.
Make sure to provide the correct path to the input file when executing the program.
## Output

The LAN Party program produces output based on the enabled tasks and writes it to the specified output file (`r.out`).

The program will generate different output depending on the tasks enabled in the configuration file.

Make sure to provide the correct path to the output file when executing the program.

## Cleanup and Resource Management

The program takes care of proper resource management by closing files and freeing allocated memory when it finishes execution.

## Checker Issues

- The checker had 2 issues: in tests 8 & 13 the last team was not supposed to exist, therefore it was deleted
