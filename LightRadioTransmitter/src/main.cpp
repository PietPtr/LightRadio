#include <iostream>
#include <SFML/Graphics.hpp>
#include <bitset>

using namespace sf;

int main()
{
    int windowWidth = 640*2;
    int windowHeight = 480*2;

    std::string datastr = "Hello, world!";
    const char* chardata = datastr.c_str();
    const int numbits = datastr.length() * 8 + 6;
    char bitdata[numbits];

    //set the first 3 bits to 0, for the corruption check later
    for (int i = 0; i < 3; i++)
        bitdata[i] = 0;

    for (int i = 0; i < datastr.length(); i++)
    {
        std::string binary = std::bitset<8>(chardata[i]).to_string();

        for (int b = 0; b < 8; b++)
        {
            bitdata[i * 8 + 3 + b] = binary[b] == '0' ? 0 : 1;
        }
    }

    for (int i = numbits - 3; i < numbits; i++)
        bitdata[i] = 1;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Float");
    window.setFramerateLimit(60);
    Time time;
    Clock clock;
    int frame = 0;

    RectangleShape rects[12] = { };

    int absoluteBitPos = 0;
    int bitFrame = 0;
    int bitFrameInterval = 2000;
    Time lastBitFrameRenew = time;

    bool callibrating = true;

    int rectIndex = 0;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            rects[rectIndex] = RectangleShape(Vector2f(windowWidth / 4, windowHeight / 3));
            rects[rectIndex].setPosition(Vector2f(x * windowWidth / 4, y * windowHeight / 3));
            rects[rectIndex].setFillColor(Color(0, 0, 0));
            rectIndex++;
        }
    }

    std::cout << numbits << " numbits\n";
    std::cout << datastr.length() << " datastr len \n";

    for (int i = 0; i < numbits * 2; i++)
    {
        std::cout << (int)bitdata[i] << " ";
    }
    std::cout << "\n";

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
                if (event.key.code == Keyboard::Return)
                {
                    callibrating = false;
                    lastBitFrameRenew = time;
                }
            }
        }
        time += clock.restart();

        if (callibrating)
        {
            for (int i = 0; i < 12; i++)
                rects[i].setFillColor(Color(0, 0, 0));

            rects[0].setFillColor(Color(255, 0, 0));
            rects[3].setFillColor(Color(0, 255, 0));
            rects[8].setFillColor(Color(0, 0, 255));
            rects[11].setFillColor(Color(255, 255, 255));
        }
        else if (!callibrating)
        {
            int rectIndex = 0;
            int relativebitpos = 0;
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    rects[rectIndex] = RectangleShape(Vector2f(windowWidth / 4, windowHeight / 3));
                    rects[rectIndex].setPosition(Vector2f(x * windowWidth / 4, y * windowHeight / 3));

                    int r = 0;
                    int g = 0;
                    int b = 0;

                    if (rectIndex != 0)
                    {
                        if (absoluteBitPos + relativebitpos < (int)numbits)
                        {
                            r = bitdata[absoluteBitPos + relativebitpos + 0] * 255;
                            g = bitdata[absoluteBitPos + relativebitpos + 1] * 255;
                            b = bitdata[absoluteBitPos +
                            relativebitpos + 2] * 255;
                        }

                        rects[rectIndex].setFillColor(Color(r, g, b));

                        relativebitpos+=3;
                    }
                    else if (rectIndex == 0)
                    {
                        if (bitFrame % 2 == 0)
                            rects[rectIndex].setFillColor(Color(255, 0, 0));
                        else if (bitFrame % 2 == 1)
                            rects[rectIndex].setFillColor(Color(0, 255, 0));
                    }

                    std::cout << absoluteBitPos + relativebitpos << " " << absoluteBitPos << "\n";

                    rectIndex++;
                }
            }
            std::cout << "\n";

            if (time.asMilliseconds() - lastBitFrameRenew.asMilliseconds() >= bitFrameInterval)
            {
                absoluteBitPos += 17;
                bitFrame++;
                lastBitFrameRenew = time;
            }

            if (absoluteBitPos > (int)numbits)
            {
                callibrating = true;
                absoluteBitPos = 0;
                bitFrame = 0;
                lastBitFrameRenew = time;
            }
        }

        window.clear(Color(0, 0, 0));

        for (int i = 0; i < 12; i++)
        {
            window.draw(rects[i]);
        }

        //std::cout << absoluteBitPos << " " << numbits << "\n";

        window.display();

        frame++;
    }

    return EXIT_SUCCESS;
}
