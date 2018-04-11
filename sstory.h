/*
 * sstory.h
 * Interactive CLI Text Adventure creation library.
 * 
 * Author: Santiago Quintero
 * Released under The MIT License
 *
 */

#ifndef SStory_h
#define SStory_h

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

// Sound handling with OpenAl
#include "ssound.h"

namespace SStory
{

class Text
{
    //! Basic String Wrapper
  protected:
    std::string body;

  public:
    Text(std::string s)
        : body(s) {}
    //! Prints the body text in standar output
    void print() const
    {
        std::cout << body << std::endl;
    }

    void pprint(const std::string &prepend) const
    {
        std::cout << prepend << " : " << body << std::endl;
    }

    void pprint(const Text &prepend) const
    {
        std::cout << prepend.body << " : " << body << std::endl;
    }

    void pprint(int prepend) const
    {
        std::cout << prepend << " : " << body << std::endl;
    }
};

class Choice
{
    //! Abstraction for the notion of multiple choices in a text adventure game.
  protected:
    std::string label;
    Text displayText;
    Text complement;
    bool withComplement;

  public:
    Choice(std::string l, std::string dt, std::string c)
        : label(l), displayText(dt), complement(c), withComplement(true) {}

    Choice(std::string l, std::string dt)
        : label(l), displayText(dt), complement(""), withComplement(false) {}

    void print(int n) const
    {
        displayText.pprint(n);
    }

    std::string execute() const
    {
        if (withComplement)
        {
            complement.pprint(displayText);
        }
        else
        {
            displayText.print();
        }
        return label;
    }
};

class ContentBody
{
    //! The basic structure of a Sub Scene
  protected:
    Text body;
    std::vector<Choice> choices;
    SSound::Sound sound;
    bool withSound;
    bool withChoices;

  public:
    ContentBody(std::string b, std::vector<Choice> c, int s)
        : body(b), choices(c), sound(s), withSound(true), withChoices(true) {}

    ContentBody(std::string b, int s)
        : body(b), sound(s), withSound(true), withChoices(false) {}

    ContentBody(std::string b, std::vector<Choice> c)
        : body(b), choices(c), sound(0), withSound(false), withChoices(true) {}

    ContentBody(std::string b)
        : body(b), sound(0), withSound(false), withChoices(false) {}

    std::string play() const
    {
        body.print();
        if (withSound)
        {
            sound.play();
        }
        if (withChoices)
        {
            int nChoices = choices.size();
            int uInput = 0;

            for (int i = 0; i < nChoices; ++i)
            {
                choices[i].print(i + 1);
            }
            uInput = read_choice(nChoices);
            /* 
            // Unvalidated input, generates loop on invalid input
            while (uInput == 0)
            {
                std::cout << "> ";
                std::cin >> uInput;
                if(uInput < 0 || uInput > nChoices )
                    uInput = 0;
            }
            */
            // Ignore the never read newline character.
            std::cin.ignore();
            return choices[uInput - 1].execute();
        }
        else
        {
            std::cout << "...";
            std::cin.ignore();
        }
        return "END";
    }

  private:
    //! Utility to validated user input and avoid undefined behaviour.
    int read_choice(int max) const
    {
        int uInput = 0;
        while (true)
        {
            std::cout << "> ";
            if (std::cin >> uInput)
            {
                if (uInput > 0 && uInput <= max)
                    return uInput;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
};

class Story
{
  protected:
    std::unordered_map<std::string, std::vector<ContentBody>> scenes;
    std::string label;

  public:
    Story() {}

    void addScene(std::string l, std::vector<ContentBody> scene)
    {
        scenes[l] = scene;
    }

    void play()
    {
        std::vector<ContentBody> currentScene;
        std::string currentLabel = "START";
        const std::string endLabel = "END";
        while (currentLabel.compare(endLabel) != 0)
        {
            if (scenes.count(currentLabel) < 1)
            {
                std::cout << "You must define an scene with label " << currentLabel << std::endl;
            }
            else
            {
                currentScene = scenes[currentLabel];
                for (const auto &content : currentScene)
                {
                    currentLabel = content.play();
                }
            }
        }
        std::cout << "The End." << std::endl;
    }
};
}

#endif //SStory_h
