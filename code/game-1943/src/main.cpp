////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 1943 - La Batalla de Midway
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/Game1943.h>
#include <mach/Machine.h>

#include <src/testing/TestTypingMessage.h>
#include <src/testing/TestCampaignResult.h>
#include <src/testing/TestMissionAbortedPresentation.h>
#include <src/testing/TestMissionCompletedPresentation.h>

void main()
{
	Machine().start(new Game1943(), "1943 - La Batalla de Midway", SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0);
//	Machine().start(new TestTypingMessage(), "1943 - TestTypingMessage", SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0);
//	Machine().start(new TestCampaignResult(), "1943 - TestCampaignResult", SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0);
//	Machine().start(new TestMissionAbortedPresentation(), "1943 - TestMissionAbortedPresentation", SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0);
//	Machine().start(new TestMissionCompletedPresentation(), "1943 - TestMissionCompletedPresentation", SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0);
}
