////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Adventure Island
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/GameAdventureIsland.h>

#include <mach/Machine.h>

#include <src/testing/entities/bonus/TestBonus_Apple.h>
#include <src/testing/entities/bonus/TestBonus_Ax.h>
#include <src/testing/entities/bonus/TestBonus_Banana.h>
#include <src/testing/entities/bonus/TestBonus_Carrot.h>
#include <src/testing/entities/bonus/TestBonus_ExtraLife.h>
#include <src/testing/entities/bonus/TestBonus_Fireball.h>
#include <src/testing/entities/bonus/TestBonus_Flower.h>
#include <src/testing/entities/bonus/TestBonus_Gamepad.h>
#include <src/testing/entities/bonus/TestBonus_Milk.h>
#include <src/testing/entities/bonus/TestBonus_Pineapple.h>
#include <src/testing/entities/bonus/TestBonus_Pot.h>
#include <src/testing/entities/bonus/TestBonus_Skate.h>
#include <src/testing/entities/bonus/TestBonus_Tomato.h>
#include <src/testing/entities/enemies/TestBat.h>
#include <src/testing/entities/enemies/TestBird.h>
#include <src/testing/entities/enemies/TestCobra.h>
#include <src/testing/entities/enemies/TestCoyote.h>
#include <src/testing/entities/enemies/TestFrog.h>
#include <src/testing/entities/enemies/TestIcicle.h>
#include <src/testing/entities/enemies/TestMonster.h>
#include <src/testing/entities/enemies/TestPooter.h>
#include <src/testing/entities/enemies/TestPulposus.h>
#include <src/testing/entities/enemies/TestRock.h>
#include <src/testing/entities/enemies/TestRockBall.h>
#include <src/testing/entities/enemies/TestSkull.h>
#include <src/testing/entities/enemies/TestSnail.h>
#include <src/testing/entities/enemies/TestSpider.h>
#include <src/testing/entities/enemies/TestSwordfish.h>
#include <src/testing/entities/enemies/TestWoodFire.h>
#include <src/testing/entities/followers/TestEggplant.h>
#include <src/testing/entities/followers/TestHoneygirl.h>
#include <src/testing/entities/TestEgg.h>
#include <src/testing/entities/TestHiddenEgg.h>
#include <src/testing/entities/TestJumpSpring.h>

#include <src/testing/entities/platforms/TestPlatformFallDown.h>
#include <src/testing/entities/platforms/TestPlatformFallUp.h>
#include <src/testing/entities/platforms/TestPlatformFixed.h>

#include <src/testing/entities/platforms/TestPlatformMoveToDown.h>
#include <src/testing/entities/platforms/TestPlatformMoveToLeft.h>
#include <src/testing/entities/platforms/TestPlatformMoveToRight.h>
#include <src/testing/entities/platforms/TestPlatformMoveToUp.h>

#include <src/testing/entities/platforms/TestPlatformScrollDown.h>
#include <src/testing/entities/platforms/TestPlatformScrollUp.h>

#include <src/testing/entities/platforms/TestPlatformZigZagHorz.h>
#include <src/testing/entities/platforms/TestPlatformZigZagVert.h>

#include <src/testing/scenes/TestSceneArea1Round1.h>
#include <src/testing/scenes/TestSceneArea1Round2.h>
#include <src/testing/scenes/TestSceneArea1Round3.h>
#include <src/testing/scenes/TestSceneArea1Round4.h>

#if 0
int main()
#else
#include <windows.h>
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	int channels = 24;
	Machine().start(new GameAdventureIsland(), "Adventure Island", SCREEN_WIDTH, SCREEN_HEIGHT, 3, channels);
//	Machine().start(new TestBonus_Apple(), "Adventure Island | Apple", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Ax(), "Adventure Island | Ax", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Banana(), "Adventure Island | Banana", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Carrot(), "Adventure Island | Carrot", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_ExtraLife(), "Adventure Island | ExtraLife", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Fireball(), "Adventure Island | Fireball", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Flower(), "Adventure Island | Flower", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Gamepad(), "Adventure Island | Gamepad", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Milk(), "Adventure Island | Milk", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Pineapple(), "Adventure Island | Pineapple", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Pot(), "Adventure Island | Pot", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Skate(), "Adventure Island | Skate", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBonus_Tomato(), "Adventure Island | Tomato", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBat(), "Adventure Island | Bat", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestBird(), "Adventure Island | Bird", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestCobra(), "Adventure Island | Cobra", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestCoyote(), "Adventure Island | Coyote", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestFrog(), "Adventure Island | Frog", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestIcicle(), "Adventure Island | Icicle", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestMonster(), "Adventure Island | Monster", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPooter(), "Adventure Island | Pooter", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPulposus(), "Adventure Island | Pulposus", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestRock(), "Adventure Island | Rock", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestRockBall(), "Adventure Island | RockBall", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestSkull(), "Adventure Island | Skull", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestSnail(), "Adventure Island | Snail", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestSpider(), "Adventure Island | Spider", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestSwordfish(), "Adventure Island | Swordfish", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestWoodFire(), "Adventure Island | WoodFire", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestEggplant(), "Adventure Island | Eggplant", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestHoneygirl(), "Adventure Island | Honeygirl", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestEgg(), "Adventure Island | Egg", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestHiddenEgg(), "Adventure Island | HiddenEgg", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestJumpSpring(), "Adventure Island | JumpSpring", SCREEN_WIDTH, SCREEN_HEIGHT, 3);

//	Machine().start(new TestPlatformFallDown(), "Adventure Island | PlatformFallDown", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformFallUp(), "Adventure Island | PlatformFallUp", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformFixed(), "Adventure Island | PlatformFixed", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformMoveToDown(), "Adventure Island | PlatformMoveToDown", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformMoveToLeft(), "Adventure Island | PlatformMoveToLeft", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformMoveToRight(), "Adventure Island | PlatformMoveToRight", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformMoveToUp(), "Adventure Island | PlatformMoveToUp", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformScrollDown(), "Adventure Island | PlatformScrollDown", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformScrollUp(), "Adventure Island | PlatformScrollUp", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformZigZagHorz(), "Adventure Island | PlatformZigZagHorz", SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//	Machine().start(new TestPlatformZigZagVert(), "Adventure Island | PlatformZigZagVert", SCREEN_WIDTH, SCREEN_HEIGHT, 3);

//	Machine().start(new TestSceneArea1Round1(), "Adventure Island | Scene Area 1 Round 1", SCREEN_WIDTH, SCREEN_HEIGHT, 3, channels);
//	Machine().start(new TestSceneArea1Round2(), "Adventure Island | Scene Area 1 Round 2", SCREEN_WIDTH, SCREEN_HEIGHT, 3, channels);
//	Machine().start(new TestSceneArea1Round3(), "Adventure Island | Scene Area 1 Round 3", SCREEN_WIDTH, SCREEN_HEIGHT, 3, channels);
//	Machine().start(new TestSceneArea1Round4(), "Adventure Island | Scene Area 1 Round 4", SCREEN_WIDTH, SCREEN_HEIGHT, 3, channels);
	return 0;
}
