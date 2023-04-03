package modele;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CountFiles {
    public static int nbFichier(String chemin) throws Exception {
        String directoryPath = chemin;

        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("sh", "-c", "ls -1 " + directoryPath + " | wc -l");

        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

        String line = reader.readLine();
        int count = Integer.parseInt(line.trim());

        int exitCode = process.waitFor();
        return count;
    }
}