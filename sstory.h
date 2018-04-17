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
#include <utility>

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
    Text(const std::string &s)
        : body(s) {}
    Text(std::string &&s)
        : body(std::move(s)) {}
    Text(const char *s)
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
    Choice(std::string l, Text dt, Text c)
        : label(l), displayText(std::move(dt)), complement(std::move(c)), withComplement(true) {}

    Choice(std::string l, Text dt)
        : label(l), displayText(std::move(dt)), complement(""), withComplement(false) {}

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
    ContentBody(Text b, std::vector<Choice> c, SSound::Sample s)
        : body(std::move(b)), choices(std::move(c)), sound(s), withSound(true), withChoices(true) {}

    ContentBody(Text b, SSound::Sample s)
        : body(std::move(b)), sound(s), withSound(true), withChoices(false) {}

    ContentBody(Text b, std::vector<Choice> c)
        : body(std::move(b)), choices(std::move(c)), sound(SSound::Sample::attack), withSound(false), withChoices(true) {}

    ContentBody(Text b)
        : body(std::move(b)), sound(SSound::Sample::attack), withSound(false), withChoices(false) {}

    std::string play() const
    {
        body.print();
        if (withSound)
        {
            sound.play();
        }
        if (withChoices)
        {
            int nChoices = 0;
            int uInput = 0;

            for (const auto &choice : choices)
            {
                choice.print(++nChoices);
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

  public:
    Story() {}

    void addScene(std::string l, std::vector<ContentBody> scene)
    {
        scenes[l] = std::move(scene);
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
