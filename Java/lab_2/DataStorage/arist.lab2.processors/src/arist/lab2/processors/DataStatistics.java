package arist.lab2.processors;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.TreeMap;


public class DataStatistics {
    public Collection<String> collect(ArrayList<String> data) {
        Collection<String> collect = new ArrayList<>();
        TreeMap<String, Integer> map = new TreeMap<String, Integer>();
        for (String help : data) {
            String[] parts = help.split("->");
            String key = parts[0];
            Integer value = Integer.parseInt(parts[1]);
            if (map.containsKey(key)) {
                map.replace(key, map.get(key) + value);
            } else {
                map.put(key, value);
            }
        }
        for (String name : map.keySet()) {
            collect.add(name + ": " + map.get(name));

        }
        return collect;
    }
}