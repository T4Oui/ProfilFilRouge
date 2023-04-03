package modele;
import java.io.File;
import java.util.Arrays;
import java.util.Comparator;

public class FileWatcher {
    private final File directoryPath;

    public FileWatcher(String path) {
        this.directoryPath = new File(path);
    }

    public String getLatestFileName() {
        File[] files = directoryPath.listFiles();
        if (files == null || files.length == 0) {
            return null;
        }

        Arrays.sort(files, Comparator.comparingLong(File::lastModified));
        return files[files.length - 1].getName();
    }
}
