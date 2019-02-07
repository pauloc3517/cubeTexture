#include <Game.h>
#include <Debug.h>

#include <fstream>
static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}


float vertices[] =
{
	-0.1f,-0.1f,0.1, // t1
	-0.1,-0.1, -0.1f,
	-0.1, 0.1, -0.1f, // t1
	0.1, 0.1,0.1, // t2
	-0.1,-0.1,0.1,
	-0.1, 0.1,0.1, // t2
	0.1,-0.1, -0.1,//t3s
	-0.1,-0.1,0.1,
	0.1,-0.1,0.1,//t3e
	0.1, 0.1,0.1,//t4s
	0.1,-0.1,0.1,
	-0.1,-0.1,0.1,//t4
	-0.1,-0.1,0.1,//t5
	-0.1, 0.1, -0.1f,
	-0.1, 0.1,0.1,//t5
	0.1,-0.1, -0.1f,//t6
	-0.1,-0.1, -0.1f,
	-0.1,-0.1,0.1,//t6
	-0.1, 0.1, -0.1f,//t7
	-0.1,-0.1, -0.1f,
	0.1,-0.1, -0.1f,//t7
	0.1, 0.1, -0.1f,//t8
	0.1,-0.1,0.1,
	0.1, 0.1,0.1,//t8
	0.1,-0.1,0.1,//t9
	0.1, 0.1, -0.1f,
	0.1,-0.1, -0.1f,//t9
	0.1, 0.1, -0.1f,//t10
	0.1, 0.1,0.1,
	-0.1, 0.1,0.1,//t10
	0.1, 0.1, -0.1f,//t11
	-0.1, 0.1,0.1,
	-0.1, 0.1, -0.1f,//t11
	0.1, 0.1, -0.1f,//t12
	-0.1, 0.1, -0.1f,
	0.1,-0.1, -0.1f//t12
};

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

Vertex vertex[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
vsid, //Vertex Shader ID
fsid, //Fragment Shader ID
progID, //Program ID
vao = 0, //Vertex Array ID
vbo[1], // Vertex Buffer ID
positionID, //Position ID
colorID, // Color ID
to,			// Texture ID 1 to 32
textureID,	//Texture ID
texelID,// Texel ID
mvpID;	//model view projection ID

//const std::string filename = "texture.tga";
const std::string filename = "cube.tga";

//const std::string filename = "minecraft.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA



unsigned char* img_data;


glm::mat4 mvp, projection, view, model;			// Model View Projection

void Game::initialize()
{
	isRunning = true;

	GLint isCompiled = 0;
	GLint isLinked = 0;
	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	/* Vertices counter-clockwise winding */

	for (int i = 0; i < 36; i++)
	{
		for (int c = 0; c < 3; c++)
		{
			vertex[i].coordinate[c] = vertices[i * 3 + c];
			std::cout << vertex[i].coordinate[c] << std::endl;
			//vertex[i].color[c] = (((c+1)* (0.1 +i))/100.0f);


		}

	}

	int i = 0;
	while (i < 36)
	{
		//purple

		if (i < 6)
		{
			//first
			vertex[i].texel[0] = 0.25f;
			vertex[i].texel[1] = 0.25f;

			//second blue
			vertex[i + 1].texel[0] = 0.25f;
			vertex[i + 1].texel[1] = 0.25f;
			//third yello
			vertex[i + 2].texel[0] = 0.25f;
			vertex[i + 2].texel[1] = 0.25f;
			//fourth green
			vertex[i + 3].texel[0] = 0.25f;
			vertex[i + 3].texel[1] = 0.25f;
			//fifth
			vertex[i + 4].texel[0] = 0.25f;
			vertex[i + 4].texel[1] = 0.25f;
			//6th
			vertex[i + 5].texel[0] = 0.25f;
			vertex[i + 5].texel[1] = 0.25f;
		}

		//blue
		else if (i < 12)
		{
			//first
			vertex[i].texel[0] = 0.25f;
			vertex[i].texel[1] = 0.3f;

			//second b
			vertex[i + 1].texel[0] = 0.25f;
			vertex[i + 1].texel[1] = 0.3f;
			//third yello
			vertex[i + 2].texel[0] = 0.25f;
			vertex[i + 2].texel[1] = 0.3f;
			//fourth green
			vertex[i + 3].texel[0] = 0.25f;
			vertex[i + 3].texel[1] = 0.3f;
			//fifth
			vertex[i + 4].texel[0] = 0.25f;
			vertex[i + 4].texel[1] = 0.3f;
			//6th
			vertex[i + 5].texel[0] = 0.25f;
			vertex[i + 5].texel[1] = 0.3f;
		}

		else if (i < 18)
		{
			//first
			vertex[i].texel[0] = 0.51f;
			vertex[i].texel[1] = 0.3f;

			//second blue
			vertex[i + 1].texel[0] = 0.51f;
			vertex[i + 1].texel[1] = 0.3f;
			//third yello
			vertex[i + 2].texel[0] = 0.51f;
			vertex[i + 2].texel[1] = 0.3f;
			//fourth green
			vertex[i + 3].texel[0] = 0.51f;
			vertex[i + 3].texel[1] = 0.3f;
			//fifth
			vertex[i + 4].texel[0] = 0.51f;
			vertex[i + 4].texel[1] = 0.3f;
			//6th
			vertex[i + 5].texel[0] = 0.51f;
			vertex[i + 5].texel[1] = 0.3f;
		}
		else if (i < 24)
			{
				//first
				vertex[i].texel[0] = 0.765f;
				vertex[i].texel[1] = 0.3f;

				//second blue
				vertex[i + 1].texel[0] = 0.765f;
				vertex[i + 1].texel[1] = 0.3f;
				//third yello
				vertex[i + 2].texel[0] = 0.765f;
				vertex[i + 2].texel[1] = 0.3f;
				//fourth green
				vertex[i + 3].texel[0] = 0.765f;
				vertex[i + 3].texel[1] = 0.3f;
				//fifth
				vertex[i + 4].texel[0] = 0.765f;
				vertex[i + 4].texel[1] = 0.3f;
				//6th
				vertex[i + 5].texel[0] = 0.765f;
				vertex[i + 5].texel[1] = 0.3f;
			}
		else if (i < 30)
			{
				//first
				vertex[i].texel[0] = 0.49f;
				vertex[i].texel[1] = 0.24f;

				//second blue
				vertex[i + 1].texel[0] = 0.49f;
				vertex[i + 1].texel[1] = 0.24f;
				//third yello
				vertex[i + 2].texel[0] = 0.49f;
				vertex[i + 2].texel[1] = 0.24f;
				//fourth green
				vertex[i + 3].texel[0] = 0.49f;
				vertex[i + 3].texel[1] = 0.24f;
				//fifth
				vertex[i + 4].texel[0] = 0.49f;
				vertex[i + 4].texel[1] = 0.24f;
				//6th
				vertex[i + 5].texel[0] = 0.49f;
				vertex[i + 5].texel[1] = 0.24f;
			}
		else
			{
				//first
				vertex[i].texel[0] = 0.01f;
				vertex[i].texel[1] = 0.49f;

				//second blue
				vertex[i + 1].texel[0] = 0.01f;
				vertex[i + 1].texel[1] = 0.49f;
				//third yello
				vertex[i + 2].texel[0] = 0.01f;
				vertex[i + 2].texel[1] = 0.49f;
				//fourth green
				vertex[i + 3].texel[0] = 0.01f;
				vertex[i + 3].texel[1] = 0.49f;
				//fifth
				vertex[i + 4].texel[0] = 0.01f;
				vertex[i + 4].texel[1] = 0.49f;
				//6th
				vertex[i + 5].texel[0] = 0.01f;
				vertex[i + 5].texel[1] = 0.49f;
			}


		i += 6;
	}
	// Save yourself time and just loop it
	for (int i = 0; i < 36; i++)
	{
		triangles[i] = i;
	}


	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// find vertexshader text and add to stream
	 std::ifstream vertexShaderText ("VertexShader.txt");

	 if (!vertexShaderText)
	 {
		 std::cout << "VertexShader.txt not found!" << std::endl;
	 }

	 // iterate through string and add ASCII contents into vertexShaderTextString
	std::string vertexShaderTextString((std::istreambuf_iterator<char>(vertexShaderText)),
		std::istreambuf_iterator<char>());


	/* Vertex Shader which would normally be loaded from an external file */

	const char* vs_src = vertexShaderTextString.c_str(); //dispay as c style string

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

						   //Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}
	
	// Load fragment shader text into stream
	std::ifstream fragmentShaderText("FragmentShader.txt");

	// check it exists
	if (!fragmentShaderText)
	{
		std::cout << "FragmentShader.txt not found!" << std::endl;
	}

	// iterate through string and add ASCII contents into fragmentShaderTextString
	std::string fragmentShaderTextString((std::istreambuf_iterator<char>(fragmentShaderText)),
		std::istreambuf_iterator<char>());


	/* fragment Shader which would normally be loaded from an external file */

	const char* fs_src = fragmentShaderTextString.c_str(); //dispay as c style string
	
	
	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}


	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, 
		img_data // image data
	);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
	mvpID = glGetUniformLocation(progID, "sv_mvp");



	// Projection Matrix 
	projection = glm::perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
	);

	// Camera Matrix
	view = glm::lookAt(
		glm::vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(0.0f, 0.0f, 0.0f),	// Camera looking at origin
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);

	// Model matrix
	model = glm::mat4(
		1.0f					// Identity Matrix
	);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		for (int i = 0; i < 36; i++)
		{

			vertex[i].texel[0] -= 0.005f;
			std::cout << "Texel 0 Vertex: " << i << " is value " << vertex[i].texel[0] << std::endl;
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		for (int i = 0; i < 36; i++)
		{

			vertex[i].texel[0] += 0.005f;
			std::cout << "Texel 0 Vertex: " << i << " is value " << vertex[i].texel[0] << std::endl;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		for (int i = 0; i < 36; i++)
		{

			vertex[i].texel[1] -= 0.005f;
			std::cout << "Texel 1 Vertex: " << i << " is value " << vertex[i].texel[1] << std::endl;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		for (int i = 0; i < 36; i++)
		{

			vertex[i].texel[1] += 0.005f;
			std::cout << "Texel 1 Vertex: " << i << " is value " << vertex[i].texel[1] << std::endl;
		}
	}


	//reset
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (int i = 0; i < 36; i++)
		{
			for (int c = 0; c < 3; c++)
			{
				vertex[i].coordinate[c] = vertices[i * 3 + c];
			}
		}
	}
	//translate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = MyVector3{ 0,0,1 };
			
			MyVector3 displace = MyVector3{ 0, 0.004f, 0 };

			MyVector3 newVec = (MyMatrix3::translation(displace) * tempVec);


			//vertex[i] = tempVec;

			vertex[i].coordinate[0] += newVec.x;
			vertex[i].coordinate[1] += newVec.y;


			
			
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// vertex index
			for (int i = 0; i < 36; i++)
			{

				MyVector3 tempVec = MyVector3{ 0,0,1 };

				MyVector3 displace = MyVector3{ 0, -0.004f, 0 };

				MyVector3 newVec = (MyMatrix3::translation(displace) * tempVec);


				//vertex[i] = tempVec;

				vertex[i].coordinate[0] += newVec.x;
				vertex[i].coordinate[1] += newVec.y;



			}
		}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = MyVector3{ 0,0,1 };

			MyVector3 displace = MyVector3{-0.004f, 0, 0 };

			MyVector3 newVec = (MyMatrix3::translation(displace) * tempVec);


			//vertex[i] = tempVec;

			vertex[i].coordinate[0] += newVec.x;
			vertex[i].coordinate[1] += newVec.y;



		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = MyVector3{ 0,0,1 };

			MyVector3 displace = MyVector3{ 0.004f, 0, 0 };

			MyVector3 newVec = (MyMatrix3::translation(displace) * tempVec);


			//vertex[i] = tempVec;

			vertex[i].coordinate[0] += newVec.x;
			vertex[i].coordinate[1] += newVec.y;



		}
	}


	//scale
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };


			MyVector3 newVec = (MyMatrix3::scale(1.002f) * tempVec);

			

			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;




		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			// vertex index
			for (int i = 0; i < 36; i++)
			{
				MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };


				MyVector3 newVec = (MyMatrix3::scale(0.998f) * tempVec);



				vertex[i].coordinate[0] = newVec.x;
				vertex[i].coordinate[1] = newVec.y;
				vertex[i].coordinate[2] = newVec.z;



			}
		}

	//scale
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

			MyVector3 displace = MyVector3{ 0, 0.0002f, 0 };

			MyVector3 newVec = (MyMatrix3::rotationZ(0.01) * tempVec);


			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;




		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

			MyVector3 displace = MyVector3{ 0, 0.0002f, 0 };

			MyVector3 newVec = (MyMatrix3::rotationX(0.01) * tempVec);


			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;




		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		// vertex index
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

			MyVector3 displace = MyVector3{ 0, 0.0002f, 0 };

			MyVector3 newVec = (MyMatrix3::rotationY(0.01) * tempVec);


			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;




		}
	}


	//std::cout << "Update up" << std::endl;

}

void Game::render()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
	CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
	model components that 'are' and 'are not' to be drawn )	*/


	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	

	//glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (VOID*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (VOID*)(7 * sizeof(float)));
	//glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * sizeof(GLfloat)));
	//glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE,0, (VOID*)(7 *  sizeof(GLfloat)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
	//std::cout << "Cleaning up" << std::endl;

	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

