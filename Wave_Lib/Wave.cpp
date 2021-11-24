#include "Wave.h"
#include <iostream>

int waveHeader::chr4toint(const char str[5])
{
	int buf = 
		((int)str[3] << 3) + 
		((int)str[2] << 2) + 
		((int)str[1] << 1) + 
		((int)str[0] << 0);
	return buf;
}

bool waveHeader::WriteWaveHeader(int freq, int len, int bytr, int channels)
{
	this->chunkID = chr4toint("RIFF");

	this->chunkSize = bytr * len * channels + 36;

	this->Format = chr4toint("WAVE");
	this->subChunkID = chr4toint("fmt ");

	this->subChunk1size = 16;
	this->audioFormat = 1;
	this->numChannels = channels;
	this->sampleRate = freq;
	this->byteRate = freq * bytr * channels;
	this->blockAlign = bytr * channels;
	this->bitsPerSample = bytr * 8;

	this->subChunk2ID = chr4toint("data");
	this->subChunk2size = freq * channels * bytr * len;

	return true;
}

int waveHeader::getFrequency()
{
	return byteRate / blockAlign;
}

int waveHeader::getLength()
{
	return subChunk2size / sampleRate / blockAlign;
}

int waveHeader::getbytePerSymbol()
{
	return blockAlign / numChannels;
}

int waveHeader::getChannels()
{
	return numChannels;
}

int Wave::dataNum()
{
	return bytePerSymbol * channelNum * frequency /*ByteRate*/ * length;
}

int Wave::indexMax()
{
	/*get END Symbol of Block Index*/
	return frequency * length;
}

Wave::Wave(int freq, int len, int bytr, int channels)
{
	frequency = freq, length = len, bytePerSymbol = bytr, channelNum = channels;
	header.WriteWaveHeader(freq, len, bytr, channels);
	data = new char[dataNum()];
}

Wave::Wave(const char* path)
{
	std::fstream fio(path, std::ios::in | std::ios::binary);
	if (fio.fail()) frequency = 0, channelNum = 0, length = 0, bytePerSymbol = 0, data = nullptr;
	else
	{
		fio.read((char*)&header, sizeof(waveHeader));
		frequency = header.getFrequency();
		length = header.getLength();
		bytePerSymbol = header.getbytePerSymbol();
		channelNum = header.getChannels();

		data = new char[dataNum()];
		for (int i = 0; i < dataNum(); i++)
		{
			fio.read(data + i, sizeof(char) * dataNum());
		}
	}
	fio.close();
}

Wave::~Wave()
{

	delete[] data;
}

bool Wave::readWave(const char* path)
{
	delete[] data;
	std::fstream fio(path, std::ios::in | std::ios::binary);
	if (fio.fail()) { frequency = 0, channelNum = 0, length = 0, bytePerSymbol = 0, data = nullptr; fio.close(); return false; }
	
	fio.read((char*)&header, sizeof(waveHeader));
	frequency = header.getFrequency();
	length = header.getLength();
	bytePerSymbol = header.getbytePerSymbol();
	channelNum = header.getChannels();

	data = new char[dataNum()];
	fio.read(data, sizeof(char) * dataNum());

	fio.close();
	return true;
}

bool Wave::writeWave(const char* path)
{
	std::fstream fio(path, std::ios::out | std::ios::binary);
	if (fio.fail()) { fio.close(); return false; }

	fio.write((char*)&header, sizeof(waveHeader));
	fio.write(data, sizeof(char) * dataNum());

	fio.close();
	return true;
}

char* Wave::operator()(int channel, int index)
{
	/*get data pointer form Block index & channel number*/
	if (channel > channelNum || index > (dataNum() / channelNum / bytePerSymbol)) return nullptr;
	return data + ((channelNum * index + channel) * bytePerSymbol);
}

