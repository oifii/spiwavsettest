////////////////////////////////////////////////////////////////
//nakedsoftware.org, spi@oifii.org or stephane.poirier@oifii.org
//
//
//2012june28, creation for building beats
//
//
//nakedsoftware.org, spi@oifii.org or stephane.poirier@oifii.org
////////////////////////////////////////////////////////////////

#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define BUFF_SIZE	2048


#include <ctime>
#include "WavSet.h"
#include "Instrument.h"
#include "InstrumentSet.h"

#include "partition.h"
#include "partitionset.h"

#include "WavSet.h"

#include <assert.h>
#include <windows.h>



// Select sample format
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif



//////////////////////////////////////////
//main
//////////////////////////////////////////
int main(int argc, char *argv[]);
int main(int argc, char *argv[])
{
    PaStreamParameters outputParameters;
    PaStreamParameters outputParametersMono;
    PaStream* stream;
    PaError err;

	////////////////////////
	// initialize port audio 
	////////////////////////
    err = Pa_Initialize();
    if( err != paNoError )
	{
		fprintf(stderr,"Error: Initialization failed.\n");
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		return -1;
	}

	outputParameters.device = Pa_GetDefaultOutputDevice(); // default output device 
	if (outputParameters.device == paNoDevice) 
	{
		fprintf(stderr,"Error: No default output device.\n");
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		return -1;
	}
	outputParameters.channelCount = 2;//pWavSet->numChannels;
	outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	outputParametersMono.device = Pa_GetDefaultOutputDevice(); // default output device 
	if (outputParametersMono.device == paNoDevice) 
	{
		fprintf(stderr,"Error: No default output device.\n");
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		return -1;
	}
	outputParametersMono.channelCount = 1;//pWavSet->numChannels;
	outputParametersMono.sampleFormat =  PA_SAMPLE_TYPE;
	outputParametersMono.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParametersMono.hostApiSpecificStreamInfo = NULL;

	//////////////////////////
	//initialize random number
	//////////////////////////
	srand((unsigned)time(0));



	/*
	//////////////////////////////////////////////////////////////////////////
	//populate InstrumentSet according to input folder (folder of sound files)
	//////////////////////////////////////////////////////////////////////////
	InstrumentSet* pInstrumentSet=new InstrumentSet;
	if(pInstrumentSet)
	{
		pInstrumentSet->Populate(wavfolder);
	}
	else
	{
		assert(false);
		cout << "exiting, instrumentset could not be allocated" << endl;
		goto error;
	}
	*/
	///////////////////////////////////////////
	//populate InstrumentSet manually from name
	///////////////////////////////////////////
	/*
	int iInstNameArraySize = 5;
	const char* pInstNameArray[] = {"piano","piano", "piano", "piano", "piano"};
	//const char* pInstNameArray[] = {"piano","guitar", "bass", "violin", "drumkit"};
	//const char* pInstNameArray[] = {"piano","guitar", "piano", "guitar", "piano"};
	//const char* pInstNameArray[] = {"piano","guitar", "otherinstruments", "drumkit", "drumkit"};
	//const char* pInstNameArray[] = {"africa","africa", "africa", "africa", "africa"};
	InstrumentSet* pInstrumentSet=new InstrumentSet;
	if(pInstrumentSet)
	{
		for(int i=0; i<iInstNameArraySize; i++)
		{
			//create each instrument individually
			Instrument* pInstrument = new Instrument;
			if(pInstrument)
			{
				//piano
				if(pInstrument->CreateFromName(pInstNameArray[i]))
				{
					//pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETINSEQUENCE);
					pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETALLATONCE);
					pInstrumentSet->instrumentvector.push_back(pInstrument);
				}
				else
				{
					cout << "exiting, instrument could not be created" << endl;
					goto error;
				}
			}
			else
			{
				cout << "exiting, instrument could not be allocated" << endl;
				goto error;
			}
		}
	}
	else
	{
		assert(false);
		cout << "exiting, instrumentset could not be allocated" << endl;
		goto error;
	}
	*/
	/*
	/////////////////////////////////////////////
	//populate InstrumentSet manually from filter
	/////////////////////////////////////////////
	//int iInstNameArraySize = 3;
	//const char* pInstNameArray[] = {"wavfolder_a_celloensemble.txt","wavfolder_a-d-e_celloensemble.txt", "wavfolder_c-f-g_celloensemble.txt"};
	//int iInstNameArraySize = 5;
	//const char* pInstNameArray[] = {"wavfolder_world-africanshakerskit.txt","wavfolder_world-bongokit.txt", "wavfolder_world-congakit.txt", "wavfolder_world-djembekit.txt", "wavfolder_world-kora.txt"};
	int iInstNameArraySize = 2;
	const char* pInstNameArray[] = {"wavfolder_synth-synthdrums-New Rave Kit Samples.txt", "wavfolder_synth-synthdrums-April Fools Kit Samples.txt"};
	InstrumentSet* pInstrumentSet=new InstrumentSet;
	if(pInstrumentSet)
	{
		for(int i=0; i<iInstNameArraySize; i++)
		{
			//create each instrument individually
			Instrument* pInstrument = new Instrument;
			if(pInstrument)
			{
				//piano
				if(pInstrument->CreateFromWavFilenamesFilter(pInstNameArray[i]))
				{
					//pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETINSEQUENCE);
					pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETALLATONCE);
					pInstrumentSet->instrumentvector.push_back(pInstrument);
				}
				else
				{
					cout << "exiting, instrument could not be created" << endl;
					goto error;
				}
			}
			else
			{
				cout << "exiting, instrument could not be allocated" << endl;
				goto error;
			}
		}
	}
	else
	{
		assert(false);
		cout << "exiting, instrumentset could not be allocated" << endl;
		goto error;
	}
	*/


	//////////////////
	//test zone, begin
	//////////////////
	/*
	///////////////////////////////////
	//play all notes of all instruments
	///////////////////////////////////
	//int numberofinstrumentsinplayback=3;
	int numberofinstrumentsinplayback=1; //one instrument at a time
	pInstrumentSet->Play(&outputParameters, fSecondsPlay, numberofinstrumentsinplayback); //each instrument will play its loaded samples sequentially
	*/
	
	/////////////////////////////
	//spread n sinusoidal samples
	/////////////////////////////
	/*
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(1.0);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30);
	pSilentWavSet->SpreadSample(6, pTempWavSet,30); //default duration and distance
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;
	*/
	
	/*
	////////////////////////////////////////////////////////////
	//spread sinusoidal sample patterned like "1000110011001100"
	////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(10); //10sec
	pSilentWavSet->SpreadSample("1000100010001000", pTempWavSet, 4, 1.0, 0.0); //pattern over 4 sec, sample duration 1.0 sec and with pattern offset of 0sec 
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;

	pTempWavSet = new WavSet;
	pTempWavSet->CreateSquare(0.25);
	pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(10); //10sec
	pSilentWavSet->SpreadSample("1000100010001000", pTempWavSet, 4, 1.0, 0.0); //pattern over 4 sec, sample duration 1.0 sec and with pattern offset of 0sec 
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;

	pTempWavSet = new WavSet;
	pTempWavSet->CreateSaw(0.25);
	pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(10); //10sec
	pSilentWavSet->SpreadSample("1000100010001000", pTempWavSet, 4, 1.0, 0.0); //pattern over 4 sec, sample duration 1.0 sec and with pattern offset of 0sec 
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;

	pTempWavSet = new WavSet;
	pTempWavSet->CreateTri(0.25);
	pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(10); //10sec
	pSilentWavSet->SpreadSample("1000100010001000", pTempWavSet, 4, 1.0, 0.0); //pattern over 4 sec, sample duration 1.0 sec and with pattern offset of 0sec 
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;
	*/

	/*
	Instrument* pInstrumentSinWav = new Instrument;
	pInstrumentSinWav->CreateWavSynth(INSTRUMENT_SYNTH_SINWAV);
	Instrument* pInstrumentSquareWav = new Instrument;
	pInstrumentSquareWav->CreateWavSynth(INSTRUMENT_SYNTH_SQUAREWAV);
	Instrument* pInstrumentSawWav = new Instrument;
	pInstrumentSawWav->CreateWavSynth(INSTRUMENT_SYNTH_SAWWAV);
	Instrument* pInstrumentTriWav = new Instrument;
	pInstrumentTriWav->CreateWavSynth(INSTRUMENT_SYNTH_TRIWAV);

	WavSet* pTempWavSet;
	
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("A4");
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromFrequency(440);
	pTempWavSet->Play(&outputParameters);

	int midinotenumber = 69;
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteNumber(midinotenumber);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet->WriteWavFile("sin.wav");
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteNumber(midinotenumber);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet->WriteWavFile("sqr.wav");
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteNumber(midinotenumber);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet->WriteWavFile("saw.wav");
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteNumber(midinotenumber);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet->WriteWavFile("tri.wav");

	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteNumber(midinotenumber+1);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteNumber(midinotenumber+2);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteNumber(midinotenumber+3);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteNumber(midinotenumber+4);
	pTempWavSet->Play(&outputParameters);

	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteNumber(midinotenumber+1);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteNumber(midinotenumber+2);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteNumber(midinotenumber+3);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteNumber(midinotenumber+4);
	pTempWavSet->Play(&outputParameters);

	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteNumber(midinotenumber+1);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteNumber(midinotenumber+2);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteNumber(midinotenumber+3);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteNumber(midinotenumber+4);
	pTempWavSet->Play(&outputParameters);

	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteNumber(midinotenumber+1);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteNumber(midinotenumber+2);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteNumber(midinotenumber+3);
	pTempWavSet->Play(&outputParameters);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteNumber(midinotenumber+4);
	pTempWavSet->Play(&outputParameters);

	delete pInstrumentSinWav;
	delete pInstrumentSquareWav;
	delete pInstrumentSawWav;
	delete pInstrumentTriWav;
	*/

	/*
	///////////
	//test mono
	///////////
	WavSet* pWavSet1 = new WavSet;
	pWavSet1->CreateSin(5.0, 44100, 1, 440);
	pWavSet1->Play(&outputParametersMono); 
	pWavSet1->WriteWavFile("sin-mono.wav");
	delete pWavSet1;
	WavSet* pWavSet2 = new WavSet;
	pWavSet2->CreateSquare(5.0, 44100, 1, 440);
	pWavSet2->Play(&outputParametersMono); 
	pWavSet2->WriteWavFile("sqr-mono.wav");
	delete pWavSet2;
	WavSet* pWavSet3 = new WavSet;
	pWavSet3->CreateSaw(5.0, 44100, 1, 440);
	pWavSet3->Play(&outputParametersMono); 
	pWavSet3->WriteWavFile("saw-mono.wav");
	delete pWavSet3;
	WavSet* pWavSet4 = new WavSet;
	pWavSet4->CreateTri(5.0, 44100, 1, 440);
	pWavSet4->Play(&outputParametersMono); 
	pWavSet4->WriteWavFile("tri-mono.wav");
	delete pWavSet4;
	*/


	Instrument* pInstrumentSinWav = new Instrument;
	pInstrumentSinWav->CreateWavSynth(INSTRUMENT_SYNTH_SINWAV);
	Instrument* pInstrumentSquareWav = new Instrument;
	pInstrumentSquareWav->CreateWavSynth(INSTRUMENT_SYNTH_SQUAREWAV);
	Instrument* pInstrumentSawWav = new Instrument;
	pInstrumentSawWav->CreateWavSynth(INSTRUMENT_SYNTH_SAWWAV);
	Instrument* pInstrumentTriWav = new Instrument;
	pInstrumentTriWav->CreateWavSynth(INSTRUMENT_SYNTH_TRIWAV);

	WavSet* pTempWavSet;
	
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("C4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("C#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("D4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("D#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("E4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("F4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("F#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("G4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("G#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("A4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("A#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSinWav->GetWavSetFromMidiNoteName("B4");
	pTempWavSet->Play(&outputParameters, 1.0);

	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("C4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("C#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("D4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("D#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("E4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("F4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("F#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("G4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("G#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("A4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("A#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSquareWav->GetWavSetFromMidiNoteName("B4");
	pTempWavSet->Play(&outputParameters, 1.0);

	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("C4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("C#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("D4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("D#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("E4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("F4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("F#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("G4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("G#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("A4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("A#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentSawWav->GetWavSetFromMidiNoteName("B4");
	pTempWavSet->Play(&outputParameters, 1.0);

	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("C4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("C#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("D4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("D#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("E4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("F4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("F#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("G4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("G#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("A4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("A#4");
	pTempWavSet->Play(&outputParameters, 1.0);
	pTempWavSet = pInstrumentTriWav->GetWavSetFromMidiNoteName("B4");
	pTempWavSet->Play(&outputParameters, 1.0);

	delete pInstrumentSinWav;
	delete pInstrumentSquareWav;
	delete pInstrumentSawWav;
	delete pInstrumentTriWav;


	/*
	//////////////////////////////////////////////////////////////////
	//spread instrument sample patterned like "1000110011001100", once
	//////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		pAnInstrument = pInstrumentSet->GetInstrumentRandomly(); //assuming 
		assert(pAnInstrument);
		pAWavSet = pAnInstrument->GetWavSetRandomly();
		assert(pAWavSet);
	}
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30); //30sec
	//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pSilentWavSet->SpreadSample("1000110011001100", pAWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	//pSilentWavSet->LoopSample(pAWavSet, -1.0, -1.0, 15.0); //from second 15, loop sample once
	pSilentWavSet->LoopSample(pAWavSet, 15.0, 0.25, 15.0); //from second 15, loop sample during 15 seconds
	pSilentWavSet->Play(&outputParameters);
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/
	/*
	////////////////////////////////////////////////////////////////////
	//spread instrument sample patterned like "1000110011001100", looped
	////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		pAnInstrument = pInstrumentSet->GetInstrumentRandomly(); //assuming 
		assert(pAnInstrument);
		pAWavSet = pAnInstrument->GetWavSetRandomly();
		assert(pAWavSet);
	}
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30); //30sec
	WavSet* pLoopWavSet = new WavSet;
	pLoopWavSet->CreateSilence(4); //4sec
	//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pLoopWavSet->SpreadSample("1000110011001100", pAWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pSilentWavSet->LoopSample(pLoopWavSet, 30.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
	pSilentWavSet->Play(&outputParameters);
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for each instrument, pick random wavset, spread wavset patterned like "1000110011001100", looped pattern and play
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30); //30sec
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			cout << endl;
			pAnInstrument = *it;
			assert(pAnInstrument);
			cout << "instrument name: " << pAnInstrument->instrumentname << endl;
			pAWavSet = pAnInstrument->GetWavSetRandomly();
			cout << "sound filename: " << pAWavSet->GetName() << endl;
			assert(pAWavSet);

			WavSet* pLoopWavSet = new WavSet;
			pLoopWavSet->CreateSilence(4); //4sec
			//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
			pLoopWavSet->SpreadSample("1000110011001100", pAWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
			pSilentWavSet->LoopSample(pLoopWavSet, 30.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
			pSilentWavSet->Play(&outputParameters);
			delete pLoopWavSet;
		}
	}
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/
	
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for each instrument, pick random wavset, spread wavset patterned like "9000220022002200", looped pattern and play
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(128); //30sec
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			cout << endl;
			pAnInstrument = *it;
			assert(pAnInstrument);
			cout << "instrument name: " << pAnInstrument->instrumentname << endl;
			//pAWavSet = pAnInstrument->GetWavSetRandomly();
			//assert(pAWavSet);
			cout << "sound filename: " << "as a function of supplied pattern" << endl;

			WavSet* pLoopWavSet = new WavSet;
			pLoopWavSet->CreateSilence(16); //4sec
			//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
			//pLoopWavSet->SpreadSamples("0003000200040005", pAnInstrument, 4, 0.5, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
			pLoopWavSet->SpreadSamples("9000220022002200400022002200220070002200220022001000220022002200", pAnInstrument, 16, 0.5, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
			pSilentWavSet->LoopSample(pLoopWavSet, 128.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
			pSilentWavSet->Play(&outputParameters);
			delete pLoopWavSet;
		}
	}
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for each instrument, pick random wavset, spread wavset patterned like "9000220022002200", looped pattern and play
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			WavSet* pSilentWavSet = new WavSet;
			pSilentWavSet->CreateSilence(32); //32sec
			if(pSilentWavSet) 
			{
				cout << endl;
				pAnInstrument = *it;
				assert(pAnInstrument);
				cout << "instrument name: " << pAnInstrument->instrumentname << endl;
				//pAWavSet = pAnInstrument->GetWavSetRandomly();
				//assert(pAWavSet);
				cout << "sound files name: " << "" << endl;

				WavSet* pLoopWavSet = new WavSet;
				pLoopWavSet->CreateSilence(16); //4sec
				//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
				pLoopWavSet->SpreadSamples("9000220022002200400022002200220070002200220022001000220022002200", pAnInstrument, 16, 0.25, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
				pSilentWavSet->LoopSample(pLoopWavSet, 32.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
				pSilentWavSet->Play(&outputParameters);
				delete pLoopWavSet;
				delete pSilentWavSet;
			}
		}
	}
	if(pTempWavSet) delete pTempWavSet;
	//goto exit;
	*/
	/*
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			string mystring = (*it)->GetWavSetPatternCodes();
			string mystring2= (*it)->GetWavSetPatternNotes();

			WavSet* pSilentWavSet = new WavSet;
			pSilentWavSet->CreateSilence(32); //32sec
			if(pSilentWavSet) 
			{
				cout << endl;
				pAnInstrument = *it;
				assert(pAnInstrument);
				cout << "instrument name: " << pAnInstrument->instrumentname << endl;
				//pAWavSet = pAnInstrument->GetWavSetRandomly();
				//assert(pAWavSet);
				cout << "sound files name: " << "" << endl;

				WavSet* pLoopWavSet = new WavSet;
				pLoopWavSet->CreateSilence(16); //16sec
				pLoopWavSet->SpreadSamples("3000220022002200300022002200220030002200220022001000220022002200", pAnInstrument, 16, 0.25, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
				pSilentWavSet->LoopSample(pLoopWavSet, 32.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
				pSilentWavSet->Play(&outputParameters);
				delete pLoopWavSet;
				delete pSilentWavSet;
			}
		}
	}
	*/
	////////////////
	//test zone, end
	////////////////



	/////////////////////
	//terminate portaudio
	/////////////////////
	Pa_Terminate();
	//if(pInstrumentSet) delete pInstrumentSet;
	printf("Exiting!\n"); fflush(stdout);
	return 0;
}

