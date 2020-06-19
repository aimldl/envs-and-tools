// winamp_playlist.cpp

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Expected Input
//bring_me_three_slippers ? -Aditi.mp3
//bring_me_three_slippers ? -Amy.mp3
//bring_me_three_slippers ? -Brian.mp3
//
// Expected Output
//#EXTM3U
//#EXTINF:1, bring_me_three_slippers ? -Aditi
//bring_me_three_slippers ? -Aditi.mp3
//#EXTINF : 1, bring_me_three_slippers ? -Amy
//bring_me_three_slippers ? -Amy.mp3
//#EXTINF : 1, bring_me_three_slippers ? -Brian
//bring_me_three_slippers ? -Brian.mp3

// Refer to https://en.wikipedia.org/wiki/M3U
// Directive                 Description	                 Example
// #EXTM3U	 File header.Must be the first line of the file. #EXTM3U
// #EXTINF	 Track information, including runtime and title. #EXTINF:191, Artist Name - Track Title
void
filename2m3u( string input_file, string output_file)
{
	ifstream ifs(input_file);
	ofstream ofs(output_file);
	stringstream ss;
	string   line;
	string   token;
	string   filename;
	string   dir_output = "output";
	int      runtime = 1;  // 1 for simplicity for now.
	int      count;

	// The first line
	ofs << "#EXTM3U" << endl; 
	while (ifs.good())
	{
		getline(ifs, line);  // bring_me_three_slippers?-Aditi.mp3
		ss << line;
		count = 0;
		while (getline(ss, token, '.'))
		{
			if (count == 0)
			{
				filename = token;
				count++;
			}
			else
			{
				break;
			}
		}
		ss.clear();
		ofs << "#EXTINF:" << runtime << "," << filename << endl;    // #EXTINF:1,bring_me_three_slippers?-Aditi
		ofs << dir_output << "/" << line << endl;					// output/bring_me_three_slippers ? -Aditi.mp3
	}
	// Output
	ifs.close();
	ofs.close();
}

void
add_ginie_ya(ofstream* ofs_ptr)
{
	*ofs_ptr << "#EXTINF:1,ginie-ya" << endl;
	*ofs_ptr << "audio_files\\ginie-ya.wav" << endl;
}

// I thought one sec will do. When I tested, 1 sec isn't enough.
// From "Bring me three slippers", the recorded audio is "three slippers."
// Use 2 seconds.
void
pause_2_secs(ofstream* ofs_ptr)
{
	*ofs_ptr << "#EXTINF:2,pause 2 secs" << endl;
	*ofs_ptr << "audio_files\\pause_2_secs.m4a" << endl;
}

void
pause_10_secs(ofstream* ofs_ptr)
{
	*ofs_ptr << "#EXTINF:10,pause 10 sec" << endl;
	*ofs_ptr << "audio_files\\pause_10_sec.m4a" << endl;
}

void
customize_m3u(string input_file, string output_file)
{
	ifstream ifs(input_file);
	ofstream ofs(output_file);
	stringstream ss;
	string   line;
	string   token;
	string   filename;
	int      runtime = 1;  // 1 for simplicity for now.
	int      count;

	// The first line
	ofs << "#EXTM3U" << endl;
	while (ifs.good())
	{
		getline(ifs, line);  // bring_me_three_slippers?-Aditi.mp3
		ss << line;
		count = 0;
		while (getline(ss, token, '.'))
		{
			if (count == 0)
			{
				filename = token;
				count++;
			}
			else
			{
				break;
			}
		}
		ss.clear();

		// Up to this point from the beginning of this function,
		// this function is identical to void filename2m3u(...).

		add_ginie_ya(&ofs);
		pause_2_secs(&ofs);

		ofs << "#EXTINF:" << runtime << "," << filename << endl;    // #EXTINF:1,bring_me_three_slippers?-Aditi
		ofs << line << endl;										// bring_me_three_slippers ? -Aditi.mp3

		pause_10_secs(&ofs);
	}
	// Output
	ifs.close();
	ofs.close();
}

int
main()
{
	string audio_file_list_en = "input\\audio_file_list_en.txt";
	string audio_file_list_ko = "input\\audio_file_list_ko.txt";
	string audio_play_list_en = "output\\audio_file_list_en.m3u8";
	string audio_play_list_ko = "output\\audio_file_list_ko.m3u8";

//	filename2m3u(audio_file_list_en, audio_play_list_en);
//	filename2m3u(audio_file_list_ko, audio_play_list_ko);

	customize_m3u(audio_file_list_en, audio_play_list_en);
	customize_m3u(audio_file_list_ko, audio_play_list_ko);

	return 0;
}