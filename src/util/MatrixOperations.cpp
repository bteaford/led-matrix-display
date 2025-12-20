#include <MatrixOperations.h>
#include <Magick++.h>
#include <magick/image.h>


namespace MatrixOperations {


    rgb_matrix::RGBMatrix* GenerateMatrix(rgb_matrix::RGBMatrix::Options matrix_options, rgb_matrix::RuntimeOptions runtime_opt, int argc, char *argv[]) {
        runtime_opt.drop_priv_user = getenv("SUDO_UID");
        runtime_opt.drop_priv_group = getenv("SUDO_GID");
        rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt);

        matrix_options.brightness = 10;
        matrix_options.cols = 64;
        matrix_options.hardware_mapping = "adafruit-hat";

        return rgb_matrix::RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
    }

    Magick::Image loadAndScaleImage(const std::string& fileName, const int width, const int height) {
        std::vector<Magick::Image> loaded_images;
        try {
            Magick::readImages(&loaded_images, fileName);
        } catch (std::exception &e) {
            if (e.what())
                fprintf(stderr, "%s\n", e.what());
            return nullptr;
        }
        Magick::Image image = loaded_images[0];
        image.scale(Magick::Geometry(width, height));
        return image;
    }

    void DisplayImage(const ImageSpec &image_spec, rgb_matrix::Canvas *canvas) {
        for (size_t y = 0; y < image_spec.image.rows(); ++y) {
            for (size_t x = 0; x < image_spec.image.columns(); ++x) {
                const Magick::Color &c = image_spec.image.pixelColor(x, y);
                if (c.alphaQuantum() < 256) {
                    canvas->SetPixel(x + image_spec.x, y + image_spec.y,
                                     MagickCore::ScaleQuantumToChar(c.redQuantum()),
                                     MagickCore::ScaleQuantumToChar(c.greenQuantum()),
                                     MagickCore::ScaleQuantumToChar(c.blueQuantum()));
                }
            }
        }
    }
}

