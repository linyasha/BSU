package arist.lab2.main;

import java.nio.file.Path;
import java.util.*;

import arist.lab2.datastorage.dataimport.*;
import arist.lab2.processors.DataStatistics;

public class Main {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Source file path not specified!");
            System.exit(0);
        }
        System.out.println("________________________________________");
        System.out.println("Data file : '" + Path.of(args[0]) + "'");
        System.out.println("Reading raw data:");
        TextFileDataSource dataSource = new TextFileDataSource();
        ArrayList<String> data = new ArrayList<String>();
        dataSource.loadData(args[0], data);
        System.out.println("________________________________________");
        DataStatistics dataStatistics = new DataStatistics();
        System.out.println(dataStatistics.collect(data));
    }
}
