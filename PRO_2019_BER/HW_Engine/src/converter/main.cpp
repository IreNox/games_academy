#include "hw/resource_tools/converter_system.h"
#include "hw/resource_tools/sound_converter.h"
#include "hw/resource_tools/texture_converter.h"

namespace hw
{
	int run()
	{
		ConverterSystem converter;

		if( !converter.create( "E:\\Development\\games_academy\\PR410\\PRO_2019_BER\\HW_Engine\\resources\\" ) )
		{
			return 1;
		}

		SoundConverter soundConverter;
		converter.registerConverter( &soundConverter );

		TextureConverter textureConverter;
		converter.registerConverter( &textureConverter );

		// TODO: iterate over all source files
		converter.queueFile( "E:\\Development\\games_academy\\PR410\\PRO_2019_BER\\HW_Engine\\assets\\checker_rgb.png" );

		if( !converter.convertAll() )
		{
			return 1;
		}

		return 0;
	}
}

int main()
{
	return hw::run();
}

