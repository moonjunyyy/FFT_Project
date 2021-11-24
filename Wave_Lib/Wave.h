#pragma once
#include <fstream>

class waveHeader {
public:
	waveHeader() {}
	int chunkID, chunkSize, Format, subChunkID, subChunk1size;
	short audioFormat, numChannels;
	int sampleRate, byteRate;
	short blockAlign, bitsPerSample;
	int subChunk2ID, subChunk2size;

	int chr4toint(const char[5]);
	bool WriteWaveHeader(int freq, int len, int bytr, int channels);
	int getFrequency();
	int getLength();
	int getbytePerSymbol();
	int getChannels();
};

class Wave
{
	waveHeader header;

public:

	char* data;
	int frequency, length, bytePerSymbol, channelNum;
	
	Wave(int freq, int len, int bytr, int channels);
	Wave(const char* path);
	~Wave();
	bool readWave(const char* path);
	bool writeWave(const char* path);

	int dataNum();
	int indexMax();

	char* operator() (int channel, int index);
};

