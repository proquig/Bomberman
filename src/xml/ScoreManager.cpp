//
// Created by pogam-_g on 5/29/16.
//

#include <fstream>
#include "xml/ScoreManager.hpp"

Bomberman::ScoreManager::ScoreManager(const std::string &path) : _path(path)
{
  std::ifstream f(path.c_str());
  tinyxml2::XMLElement *root = nullptr;
  bool fileLoaded = false;

  if (f.good())
    {
      root = _doc.FirstChildElement();
      if (root != nullptr && root->FirstChildElement("Scores") != nullptr)
	{
	  this->_doc.LoadFile(path.c_str());
	  fileLoaded = true;
	}
    }

  if (!fileLoaded)
    {
      if (root == nullptr)
	root = _doc.FirstChildElement();

      tinyxml2::XMLElement *score = this->_doc.NewElement("Scores");
      root->InsertEndChild(score);
      this->_doc.SaveFile(path.c_str());
    }
}

void
Bomberman::ScoreManager::SaveScore(const Score &score)
{
  tinyxml2::XMLElement *element = this->_doc.NewElement("score");
  element->SetAttribute("playerName", score.getName().c_str());
  element->SetAttribute("gameStart", (unsigned int) score.getGameStart());
  element->SetAttribute("gameEnd", (unsigned int) score.getGameEnd());
  element->SetAttribute("score", score.getScore());

  this->_doc.RootElement()->FirstChildElement("Scores")->InsertEndChild(element);
  this->_doc.SaveFile(this->_path.c_str());
}

std::vector<Bomberman::Score> Bomberman::ScoreManager::loadScores()
{
  std::vector<Bomberman::Score> scores;
  tinyxml2::XMLElement *elements = this->_doc.RootElement()->FirstChildElement("Scores");

  for (tinyxml2::XMLElement* child = elements->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
      Score score = Score(child->Attribute("playerName"), std::stol(child->Attribute("gameStart")),
			  std::stol(child->Attribute("gameEnd")), std::stoi(child->Attribute("score")));
      scores.push_back(score);
    }

  return scores;
}
