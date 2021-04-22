package arist.lab2.datastorage.dataimport;

public class DataChecker {

    public static void checkDataItem(String line) throws Exception {
        String[] parts = line.split("->");
        if (parts.length == 1) {
            throw new Exception("Error in line: " + line + " - no one separator");
        }
        if (parts.length > 2) {
            throw new Exception("Error in line: " + line + " - multiple separators");
        }

        for (int i = 0; i < parts[0].length(); i++) {
            if (!(Character.isAlphabetic(parts[0].charAt(i)) || parts[0].charAt(i) == '-')) {
                throw new Exception("Error in line: " + line + " - invalid lumber name");
            }
        }
        for (int i = 0; i < parts[1].length(); i++) {
            if (!Character.isDigit(parts[1].charAt(i))) {
                throw new Exception("Error in line: " + line + " - invalid footage");
            }
        }
    }
}
