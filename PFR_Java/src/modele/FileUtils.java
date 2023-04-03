package modele;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class FileUtils {
    private static List<String> previousFileList = new ArrayList<>();

    public static List<String> getNewFilesInDirectory(String directoryPath) {
        File directory = new File(directoryPath);

        if (directory.exists() && directory.isDirectory()) {
            String[] fileList = directory.list();
            List<String> currentFileList = Arrays.asList(fileList);
            List<String> newFileList = new ArrayList<>(currentFileList);
            newFileList.removeAll(previousFileList);
            previousFileList = currentFileList;
            return newFileList;
        } else {
            return new ArrayList<>();
        }
    }
}
