void image_preprocessing (unsigned char ** h_inputImageRGBA,
                          unsigned char ** h_outputImageRGBA,
                          unsigned char ** d_inputImageRGBA,
                          unsigned char ** d_outputImageRGBA,
                          unsigned char ** d_redBlurred,
                          unsigned char ** d_greenBlurred,
                          unsigned char ** d_blueBlurred,
                          float ** h_filter,
                          int * filterWidth,
                          const std::string &filename);
