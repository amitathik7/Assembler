# Assembler: A Limit Order Book System

## Motivation
I started Assembler to learn how financial trading systems work and how to write fast C++ software. LOB stands for Limit Order Book, the data structure that exchanges use to match buyers and sellers. It's a system where both latency and correctness matter. The name comes from Factorio because Factorio assemblers operate in a very similar manner. They match different ingredients (buy and sell orders) together to product an output (an order matching).

## Features

## Status

## Build and Run
To build the project run:
```
cmake -S . -B build
cmake --build build
```

## Architecture Overview

## Testing
To test the project, first build it and then run:
```
ctest --test-dir build
```

## Roadmap

