/*
 * Copyright (c) 2012 Maciej Niedzielski
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2014 Kevin Smith and Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace Swift {

	class HighlightRule;

	class HighlightAction {
		public:
			HighlightAction() : highlightText_(false), playSound_(false) {}

			bool highlightText() const { return highlightText_; }
			void setHighlightText(bool highlightText);

			/**
			* Gets the foreground highlight color. If the string is empty, assume a default color.
			*/
			const std::string& getTextColor() const { return textColor_; }
			void setTextColor(const std::string& textColor) { textColor_ = textColor; }

			/**
			* Gets the background highlight color. If the string is empty, assume a default color.
			*/
			const std::string& getTextBackground() const { return textBackground_; }
			void setTextBackground(const std::string& textBackground) { textBackground_ = textBackground; }

			bool playSound() const { return playSound_; }
			void setPlaySound(bool playSound);

			/**
			* Gets the sound filename. If the string is empty, assume a default sound file.
			*/
			const std::string& getSoundFile() const { return soundFile_; }
			void setSoundFile(const std::string& soundFile) { soundFile_ = soundFile; }

			bool isEmpty() const { return !highlightText_ && !playSound_; }

		private:
			friend class boost::serialization::access;
			template<class Archive> void serialize(Archive & ar, const unsigned int version);

			bool highlightText_;
			std::string textColor_;
			std::string textBackground_;

			bool playSound_;
			std::string soundFile_;
	};

	template<class Archive>
	void HighlightAction::serialize(Archive& ar, const unsigned int /*version*/)
	{
		ar & highlightText_;
		ar & textColor_;
		ar & textBackground_;
		ar & playSound_;
		ar & soundFile_;
	}

}
