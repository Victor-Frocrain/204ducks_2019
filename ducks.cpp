/*
** EPITECH PROJECT, 2020
** ducks
** File description:
** ducks.cpp
*/

#include "ducks.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <time.h>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

int parseArgs(char *arg1, Datas &datas)
{
    std::string s1(arg1);

    for (size_t i = 0; i < s1.length(); i++) {
        if ((s1[i] < '0' || s1[i] > '9') && s1[i] != '.')
            return MY_ERROR;
    }
    datas.a = std::stod(s1);
    if (datas.a < 0 || datas.a > 2.5)
        return MY_ERROR;
    return MY_SUCCESS;
}

double computeProb(double a, double prob)
{
    return (-prob * std::exp(-a) - (4.0 - 3.0 * prob) / 2.0 * std::exp(-2.0 * a) - (2.0 * prob - 4.0) / 4.0 * std::exp(-4.0 * a));
    //res = a * exp(-t) + (4 - 3 * a) * exp(-2 * t) + (2 * a - 4) * exp(-4 * t)
}

int computeBackTime(double min, double a)
{
    double i = 1.0;
    for (i = 1.0; computeProb(i / 60.0, a) - computeProb(0.0, a) < min; i++);
    return i;
}

std::string computeMinutes(int time)
{
    return std::to_string(time / 60);
}

std::string computeSeconds(int time)
{
    std::string seconds = "";

    seconds += std::to_string(time % 60 / 10);
    seconds += std::to_string(time % 10);
    return seconds;
}

double computeEsp(double a)
{
    //double p = 0.0;
    double sd = 0.0;
    double esp = 0.0;
    for (double t = 0.0; t < 99.999; t += 0.001) {
        //p += (computeProb(a, t) / 10);
        esp += t * (computeProb(t, a) / 10);
    }
    esp /= 99.999;
    return esp;
}

int computeAll(Datas &datas)
{
    double prob = 0;
    double ret = 0;
    double tr = 0;
    int n = 0;

    std::cout << std::fixed << std::setprecision(3);
    /*while (prob < 99.9999) {
        prob += computeProb(datas.a, tr) / 10;
        ret += (computeProb(datas.a, tr) / 10) * tr;
        tr += 0.001;
    }
    ret /= 99.9999;*/
    //ret += 1.0/60;
    //ret = computeProb(datas.a, 99.9999);
    //n = computeProb(datas.a, 60);
    //n = datas.a * 51;
    
    double p = 0, r = 0, i = 0, d = 0;
    for (; p < 99.9999; i += 0.001) {
        p -= computeProb(datas.a, i) / 10.0;
        r -= ((computeProb(datas.a, i)) / 10.0) * i;
    }
    std::cerr << r << std::endl;
    //r += 30;
    //r /= 99.9999;
    std::cerr << r << std::endl;
    //r /= 2.5;
    r *= 1.0/60;
    std::cerr << r << std::endl;
    for (; i > 0; i -= 0.001)
        d += pow(i - r, 2) * (computeProb(datas.a, i) / 10);
    d = pow(d / 99.9999, 0.5);

    double esp = computeEsp(datas.a);
    //div_t res = std::div(esp, 60);
    //std::modf(esp * 60, 60);
    //std::cout << esp << std::endl;
    n = computeBackTime(0, datas.a);
    std::cout << "Average return time: " << computeMinutes(r) << "m " << computeSeconds(r) << "s" << std::endl;

    //double d = 0;

    std::cout << "Standard deviation: " << d << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Time after which 50% of the ducks are back: ";
    n = computeBackTime(0.499, datas.a);
    std::cout << computeMinutes(n) << "m " << computeSeconds(n) << "s" << std::endl;

    std::cout << "Time after which 99% of the ducks are back: ";
    n = computeBackTime(0.9899, datas.a);
    std::cout << computeMinutes(n) << "m " << computeSeconds(n) << "s" << std::endl;

    std::cout << "Percentage of ducks back after 1 minute: ";
    std::cout << (computeProb(1, datas.a) - computeProb(0, datas.a)) * 100 << "%" << std::endl;

    std::cout << "Percentage of ducks back after 2 minutes: ";
    std::cout << (computeProb(2, datas.a) - computeProb(0, datas.a)) * 100 << "%" << std::endl;
    return MY_SUCCESS;
}

int ducks(int ac, char **args)
{
    int result = MY_SUCCESS;
    Datas datas;

    if (ac != 2)
        result = MY_ERROR;
    else {
        std::string arg(args[1]);
        if (arg == "-h")
            dispHelp();
        else if (parseArgs(args[1], datas) == MY_ERROR)
            return MY_ERROR;
        else
            result = computeAll(datas);
    }
    return result;
}