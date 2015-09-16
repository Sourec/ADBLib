#include <WPILib.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "../misc/Equation.h"
#include "../../lib/pugixml/pugixml.hpp"
#include "../../lib/hydra/Logger.h"
using std::unordered_map;
using std::vector;
using std::string;

namespace ADBLib
{


	/**
	 * @brief Internal use only. Stores control information.
	 */
	class ctrlCfg
	{
	public:
		ctrlCfg();
		enum {BUTTON, JOYSTICK} type;	//!< The type of control this is.
		unsigned int id;				//!< Control ID, needed regardless of button vs joystick
		bool inverse;					//!< Inverse - if button, inverts. If joystick, flips the axis... sort of
		struct btnCfg
		{
			~btnCfg();
			bool toggle;
			double cooldown;
			Timer* cooldownTimer; //TIMERS ARE COPY/ASSIGN PROTECTED! GAAAAHHHHH!
		} btn;
		struct jysCfg
		{
			double maxVal;				//!< Minimum value for a joystick. Allows control scaling.
			double minVal;				//!< Maximum value for a joystick. Allows control scaling.
			double deadzone;			//!< Deadzone to use
			Equation equ;
		} jys;
	};



	/**
	* @brief A wrapper class for the WPILib Joystick class, adding some stuff to take the headache out of working with raw inputs
	*/
	class Controller
	{
	public:
		Controller();
		~Controller(); //WARNING - DELETES THE JOYSTICK!
		bool getButtonRaw(int ID);
		double getJoystickRaw(int ID);
		void setJoystick(Joystick* newJoystick);
		void setRumble(Joystick::RumbleType side, float intensity = 1.f);
		void parseConfig(string filename);
		void switchProfile(string profileName);
		double operator[](const string& name);
	protected:
		unordered_map<string, unordered_map<string, ctrlCfg>> profiles;
		string currentProfile;
		Joystick* joystick;
	};
}
