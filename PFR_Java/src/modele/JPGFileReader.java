package modele;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class JPGFileReader {
	
    public static BufferedImage readJPGFile(String fileName) throws IOException {
        File file = new File(fileName);
        BufferedImage image = ImageIO.read(file);
        return image;
    }
}
