package arist.lab2.datastorage.dataimport;

import java.io.*;
import java.nio.charset.Charset;
import java.util.List;

public class TextFileDataSource {
    public void loadData(String filename, List<String> data) {
        try (BufferedReader src = new BufferedReader(new FileReader(filename, Charset.forName("windows-1251")))) {

            String line;
            while ((line = src.readLine()) != null) {
                try {
                    DataChecker.checkDataItem(line);
                    data.add(line);
                    System.out.println(" '" + line + "' -> loaded");
                }
                catch (Exception e) {
                    System.out.println(e.getMessage());
                }
            }
        }
        catch (FileNotFoundException e) {
            System.out.println("File '" + filename + "' not found.");
        }
        catch (IOException e) {
            System.out.println("File error: '" + filename + "'.");
        }
    }
}
