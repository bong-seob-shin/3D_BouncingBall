#include "loadObj.cpp"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GRAVITY 0.03
#define BLOCKNUMBER 74

using namespace std;

// 내일 할거
// 1.카메라완성 : 회전 된 상태에서 키보드 누르면 공 뒤로 다시 리셋//DONE
// 2. 아이템 블럭 만들기 : 2단 점프 블록, 밟으면 깨지는 블록, 밟으면 직선 로켓 블록(입력 없으면 쭉 날아감), 움직이는 블록//DONE
// 3. 맵 만들기 : 위치값(vec3) 담는 vector -> 인덱스별로 블록,아이템블록 넣어주기
// 4. 세이브 포인트 : 죽었을 때 부활 위치 지정 -> 세이브 포인트에 풍차 띄우기
// *추가: 프로펠러 같은거 블럭에 붙이기
float vertexSquare[216] = {

   -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,//A
   1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,//B
   -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,//D
   -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,//D
   1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,//B
   1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,//C
   -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,//
   1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,//
   -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,//
   1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,//
   1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,//
   -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,//
   -1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f,//
   -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,//
   -1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//
   -1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//
   -1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f,//
   -1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//
   -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,//
   1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,//
   -1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,//
   -1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,//
   1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,//
   1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,//
   -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,//E
   1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,//F
   -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,//A
   -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,//A
   1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,//F
   1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,//B
   1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,//B
   1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,//G
   1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,//C
   1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,//G
   1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,//B
   1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f//F

};

const float TriangleVertexData[] =
{
0.0, 0.2,0.0, 1.0, 0.0, 0.0, 0.0,1.0,
0.0,-0.2,0.0, 0.0, 0.0, 1.0, 0.0,0.0,
0.4, 0.0,0.0, 0.0, 0.0, 0.0, 1.0,0.5
};

float RectVertexData1[] = {
   -0.3,-0.3,0,   0.0,1.0,0.0,   0.0,0.0,
   0.3,-0.3,0,    0.0,1.0,0.0,   1.0,0.0,
   0.3,0.3,0,     0.0,1.0,0.0,    1.0,1.0,
};
float RectVertexData2[] = {
   0.3,0.3,0.0,    0.0,1.0,0.0,     1.0,1.0,
   -0.3,0.3,0.0,   0.0,1.0,0.0,     0.0,1.0,
   -0.3,-0.3,0.0,  0.0,1.0,0.0,     0.0,0.0,
};

glm::vec3 block_pos[BLOCKNUMBER] = { glm::vec3(0,0,0), glm::vec3(0,0,5),glm::vec3(0,0,11),glm::vec3(0,0,18),glm::vec3(0,0,26),//4
glm::vec3(0,0,36),glm::vec3(7,0,38),glm::vec3(14,0,36),glm::vec3(21,0,33),glm::vec3(27,0,35),//9
glm::vec3(35,0,37),glm::vec3(35,-2,42),glm::vec3(35,-4,48),glm::vec3(35,0,55),glm::vec3(35,4,60),//14
glm::vec3(35,0,70),glm::vec3(40,3,73),glm::vec3(46,6,69),glm::vec3(55,2,70),glm::vec3(65,0,66),//19
glm::vec3(71,0,72),glm::vec3(71,0,78),glm::vec3(71,0,88),glm::vec3(71,0,93),glm::vec3(75,0,100),//24
glm::vec3(80,0,108),glm::vec3(70,-2,118),glm::vec3(63,5,118),glm::vec3(54,2,108),glm::vec3(44,-2,114),//29
glm::vec3(39,0,117),glm::vec3(39,0,125),glm::vec3(39,0,131),glm::vec3(33,0,138),glm::vec3(27,-1,145),//34
glm::vec3(34,0,150),glm::vec3(40,-3,150),glm::vec3(46,-5,153),glm::vec3(53,-7,150),glm::vec3(58,-6,145),glm::vec3(66,-6,146),//40//같
glm::vec3(40,3,150),glm::vec3(46,5,153),glm::vec3(53,5,150),glm::vec3(58,3,145),//44//같
glm::vec3(66,0,146),glm::vec3(66,0,150),glm::vec3(66,0,170),glm::vec3(63,0,175),glm::vec3(63,-3,193),//49
glm::vec3(66,-5,198),glm::vec3(70,-5,201),glm::vec3(117,-6,201),glm::vec3(114,0,205),glm::vec3(80,0,205),//54
glm::vec3(75,3,205),glm::vec3(75,3,210),glm::vec3(81,1,218),glm::vec3(81,-1,227),glm::vec3(83,0,236),//59
glm::vec3(83,-2,256),glm::vec3(80,-1,262),glm::vec3(50,-3,262),glm::vec3(50,-5,282),glm::vec3(54,-5,287),//64
glm::vec3(54,1,293),glm::vec3(57,0,303),glm::vec3(63,-3,312),glm::vec3(63,-5,312),glm::vec3(63,-7,312),//69
glm::vec3(63,-9,312),glm::vec3(86,-9,312),glm::vec3(86,-11,350),glm::vec3(86,3,362)
};
enum BlockType
{
	NORMAL,
	DOUBLEJUMP,
	BROKEN,
	ROCKET_FRONT,
	ROCKET_RIGHT,
	ROCKET_LEFT,
	MOVING_RL,
	MOVING_FB,
	CLEAR,
	UP
};

// 진행 방향
enum Dir
{
	FRONT,
	LEFT,
	RIGHT
};

//bool type
bool is_W_pressed = false;
bool is_A_pressed = false;
bool is_S_pressed = false;
bool is_D_pressed = false;
// 블록 설명 텍스쳐 한번만 초기화
bool is_tuto_init = false;
unsigned char* tuto_image1;
unsigned char* tuto_image2;
// 바닥(용암) 텍스쳐 한번만 초기화
bool is_lava_init = false;
unsigned char* lava_image1;
unsigned char* lava_image2;
// 클리어 화면 한번만 초기화
bool is_clear_init = false;
unsigned char* clear_image1;
unsigned char* clear_image2;
// 쉐이더 한번만 초기화
bool is_shader1_init = false;
bool is_shader2_init = false;

//치트 블록 인덱스
int block_cheat_index = 0;

//obj 파일 불러오는것
int sphere_vertex_size = loadObj("Sphere.obj");

//텍스쳐 변수
int widthImage, heightImage, numberOfChannel;
class C_PlayerBall
{
public:
	C_PlayerBall()
	{
		Vpos = block_pos[0];
		pos_x = Vpos.x;
		pos_y = Vpos.y;
		pos_z = Vpos.z;

		strat_pos_x = 0.0f;
		start_pos_y = 0.0f;
		start_pos_z = 0.0f;

		start_bounce_speed = 0.45f;
		bounce_speed = start_bounce_speed;
		radian = 0.5f;//
		TR = glm::mat4(1.0f);
		ball_translater = glm::mat4(1.0f);
		center_vertex = glm::vec4(0, 0, 0, 1);

		is_on_jump_block = false;
		is_on_rocket_front = false;
		is_on_rocket_left = false;
		is_on_rocket_right = false;
		is_bouncing = true;
		dir = FRONT;
		is_regen = false;

	}
	~C_PlayerBall() {}

public:
	void Move(GLuint shaderprogramID)
	{
		TR = glm::mat4(1.0f);
		ball_translater = glm::mat4(1.0f);
		ball_scaler = glm::mat4(1.0f);//
		center_vertex = glm::vec4(0, 0, 0, 1);

		unsigned int transformLocation = glGetUniformLocation(shaderprogramID, "model");

		ball_translater = glm::translate(ball_translater, glm::vec3(-pos_x, pos_y, pos_z));
		ball_scaler = glm::scale(ball_scaler, glm::vec3(0.5f, 0.5f, 0.5f));//
		center_vertex = ball_translater * ball_scaler * center_vertex;//

		//cout << "Sphere!! x :" << center_vertex.x << " y : " << center_vertex.y << " z :" << center_vertex.z << endl;

		TR = TR * ball_translater * ball_scaler;//

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(TR));
	}
public:
	//공의 위치
	float pos_x;
	float pos_y;
	float pos_z;

	//공의 반지름//
	float radian;

	//공 시작 위치(젠 위치)
	float strat_pos_x;
	float start_pos_y;
	float start_pos_z;

	// 공 기본 튀기는(y축) 속도
	float start_bounce_speed;
	// 공 튀기는 속도
	float bounce_speed;

	glm::mat4 ball_translater;
	glm::mat4 TR;
	glm::mat4 ball_scaler;
	glm::vec4 center_vertex;

	// 공이 2단 점프 블록과 충돌했는지
	bool is_on_jump_block;
	// 공이 특정 방향 로켓 블록과 충돌했는지
	bool is_on_rocket_front;
	bool is_on_rocket_left;
	bool is_on_rocket_right;
	// 로켓블록 움직임 멈추기
	bool is_stop;
	//위치 벡터 배열
	glm::vec3 Vpos;

	//살아나는지
	bool is_regen;

	// 공이 바운싱하고 있는지(로켓 블록과 충돌 시 바운싱 멈춤)
	bool is_bouncing;

	//클리어 블록과 충돌
	bool is_clear;

	// 진행 방향
	Dir dir;
};
C_PlayerBall ball{};

class C_Block
{
public:
	C_Block()
	{
		is_right = true;
		is_left = false;
		is_front = true;
		is_back = false;
		is_up = false;
		is_save_point = false;
		is_saved = false;
		speed = ((rand() % 20) + 1) / 100.0f;
		is_dir_change = false;
		if (speed <= 0.03f)
			speed = 0.1f;
	}
public:
	void Set(GLuint shaderprogramID, glm::vec3 setpos, BlockType settype)
	{
		TR = glm::mat4(1.0f);
		block_translater = glm::mat4(1.0f);
		moving_translater = glm::mat4(1.0f);
		center_vertex = glm::vec4(0, 0, 0, 1);
		type = settype;
		vPos = setpos;
		is_broken = false;
		unsigned int transformLocation = glGetUniformLocation(shaderprogramID, "model");
		int objColorLocation = glGetUniformLocation(shaderprogramID, "objectColor");
		int alpaPosLocation = glGetUniformLocation(shaderprogramID, "alpa");


		block_translater = glm::translate(block_translater, glm::vec3(-vPos.x, vPos.y, vPos.z));
		moving_translater = glm::translate(moving_translater, glm::vec3(dx, dy, dz));

		center_vertex = moving_translater * block_translater * center_vertex;

		//cout << "Block!! x :" << center_vertex.x << " y : " << center_vertex.y << " z :" << center_vertex.z << endl;

		TR = TR * moving_translater * block_translater;
		if (type == DOUBLEJUMP) {
			if (is_saved) {
				glUniform3f(objColorLocation, 0.2, 0.0, 1.0);
				glUniform1f(alpaPosLocation, 1.0f);
			}
			else {
				glUniform3f(objColorLocation, 0.0, 0.0, 1.0);
				glUniform1f(alpaPosLocation, 1.0f);

			}
		}
		else if (type == MOVING_RL || type == MOVING_FB) {
			glUniform3f(objColorLocation, 1.0, 0.0, 1.0);
			glUniform1f(alpaPosLocation, 1.0f);

		}
		else if (type == BROKEN) {
			glUniform3f(objColorLocation, 0.0, 1.0, 1.0);
			glUniform1f(alpaPosLocation, 0.3f);

		}
		else if (type == ROCKET_FRONT || type == ROCKET_LEFT || type == ROCKET_RIGHT) {
			glUniform3f(objColorLocation, 1.0, 1.0, 0.0);
			glUniform1f(alpaPosLocation, 1.0f);

		}
		else if (type == UP || type == CLEAR) {
			glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
			glUniform1f(alpaPosLocation, 1.0f);

		}
		else {
			if (is_saved) {
				glUniform3f(objColorLocation, 1.0, 0.5, 0.0);
				glUniform1f(alpaPosLocation, 1.0f);

			}
			else {
				glUniform3f(objColorLocation, 0.0, 1.0, 0.0);
				glUniform1f(alpaPosLocation, 1.0f);
			}
		}

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(TR));
	}
	void Move()
	{
		if (type == MOVING_RL)
		{
			if (is_right && center_vertex.x <= -vPos.x + 4.0f)
			{
				dx += speed;
			}
			else
			{
				is_right = false;
				is_left = true;
			}
			if (is_left && center_vertex.x >= -vPos.x - 4.0f)
			{
				dx -= speed;
			}
			else
			{
				is_left = false;
				is_right = true;
			}
		}
		else if (type == MOVING_FB)
		{
			if (is_front && center_vertex.z <= vPos.z + 4.0f)
			{
				dz += speed;
			}
			else
			{
				is_front = false;
				is_back = true;
			}
			if (is_back && center_vertex.z >= vPos.z - 4.0f)
			{
				dz -= speed;
			}
			else
			{
				is_back = false;
				is_front = true;
			}
		}
		else if (type == UP)
		{
			if (ball.is_regen)
			{
				dy = 0;
				is_up = false;
			}
			else if (is_up) {
				dy += speed;
			}
		}
	}
public:
	glm::mat4 block_translater;
	// 움직이는 블록 이동행렬
	glm::mat4 moving_translater;
	glm::mat4 TR;
	glm::vec4 center_vertex;

	//블럭 길이 1cm
	float half_cm = 0.5f;//block half Cm
	// 블럭 타입
	BlockType type;
	// 부서진 블록 처리
	bool is_broken;
	// 위치 저장 변수
	glm::vec3 vPos;
	// MOVING 타입일 때 블록 이동량
	float dx;
	float dy;
	float dz;
	// MOVING 타입일 때 블록 speed
	float speed;

	// MOVING 타입일때 블록 이동방향
	bool is_right;
	bool is_left;
	bool is_front;
	bool is_back;
	bool is_up;
	//세이브 포인트 인지
	bool is_save_point;
	// 볼이 세이브 되었는지
	bool is_saved;
	// 방향 전환 설정
	bool is_dir_change;
	// 충돌시 볼의 진행 방향 설정
	Dir dir;
};


class C_Camera
{
public:
	C_Camera()
	{
		//카메라 좌표
		camera_x = 0.0f;
		camera_y = 20.0f;
		camera_z = 20.0f;
		//카메라 움직일때 더해주는 좌표(이동량)
		camera_move_x = 0.0f;
		camera_move_y = 0.0f;
		camera_move_z = 0.0f;
		is_Q_pressing = false;
		is_E_pressing = false;
		is_Q_up = false;
		is_E_up = false;
		is_P_pressed = false;
		//카메라 회전각도
		camera_angle = 0.0f;
		cam_angle_by_dir = 0.0f;
	}
	~C_Camera() {}

	void CameraSet(GLuint shaderprogramID, C_PlayerBall ball)
	{
		unsigned int projectionLoccation = glGetUniformLocation(shaderprogramID, "projection");
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians((float)45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(projectionLoccation, 1, GL_FALSE, &projection[0][0]);

		unsigned int viewLocation = glGetUniformLocation(shaderprogramID, "view");

		//카메라 파라미터
		view = glm::mat4(1.0f);
		cameraPos = glm::vec3(camera_x, camera_y, -camera_z);
		cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		cameraDirection = glm::normalize(cameraPos - cameraTarget);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		cameraUp = glm::cross(cameraDirection, cameraRight);
		camera_translater = glm::mat4(1.0f);
		camera_rotater = glm::mat4(1.0f);

		//cout << "cam X:" << camera_x << " cam Y:" << camera_y << " cam Z:" << camera_z << endl;
		if (ball.is_clear)
		{
			if (camera_y < 50.0f)
			{
				camera_y += 0.3f;
				if (camera_angle <= 180.0f)
					camera_angle += 1.0f;
			}
			else
			{
				camera_angle = 180.0f;
				if (camera_z < 130.0f)
					camera_z += 0.3f;
			}
		}
		else if (!is_Q_pressing && !is_E_pressing /*&& !ball.is_clear*/)
		{
			if (ball.dir == RIGHT)
			{
				if (camera_angle < 90.0f)
				{
					if (is_Q_up || is_E_up || is_M_up)
					{
						camera_angle = 90.0f;
					}
					else
						camera_angle += 5.0f;
				}
				else /*if (camera_angle >= 91.0f)*/
				{
					camera_angle = 90.0f;
				}
				//cam_angle_by_dir = 90.0f;
			}
			else if (ball.dir == LEFT)
			{
				if (camera_angle > -90.0f)
				{
					if (is_Q_up || is_E_up || is_M_up)
					{
						camera_angle = -90.0f;
					}
					else
						camera_angle -= 5.0f;
				}
				else
					camera_angle = -90.0f;
				//cam_angle_by_dir = -90.0f;
			}
			else if (ball.dir == FRONT)
			{
				if (camera_angle > 0)
				{
					if (is_Q_up || is_E_up || is_M_up)
					{
						camera_angle = 0.0f;
					}
					else
						camera_angle -= 5.0f;
				}
				else if (camera_angle < 0)
				{
					if (is_Q_up || is_E_up || is_M_up)
					{
						camera_angle = 0.0f;
					}
					else
						camera_angle += 5.0f;
				}
				else
					camera_angle = 0.0f;
				//cam_angle_by_dir = 0.0f;
			}
			is_Q_up = false;
			is_E_up = false;
			is_M_up = false;
		}
		// 카메라가 공 뒤에 고정
		if (is_P_pressed && !ball.is_clear)
		{
			if (ball.dir == RIGHT)
			{
				center_vertex.x = ball.center_vertex.x - 10.0f;
				center_vertex.y = -ball.center_vertex.y + 10.0f; // 공 튀기는거 까지 따라가게
				center_vertex.z = -ball.center_vertex.z;
			}
			else if (ball.dir == LEFT)
			{
				center_vertex.x = ball.center_vertex.x + 10.0f;
				center_vertex.y = -ball.center_vertex.y + 10.0f; // 공 튀기는거 까지 따라가게
				center_vertex.z = -ball.center_vertex.z;
			}
			else
			{
				center_vertex.x = ball.center_vertex.x;
				center_vertex.y = -ball.center_vertex.y + 10.0f; // 공 튀기는거 까지 따라가게
				center_vertex.z = -ball.center_vertex.z - 10.0f;
			}
		}
		else // 관측자 시점
		{
			center_vertex.x = ball.center_vertex.x;
			center_vertex.y = 0.0f;
			center_vertex.z = -ball.center_vertex.z;
		}
		//camera_translater = glm::translate(camera_translater, glm::vec3(camera_move_x, camera_move_y, camera_move_z));



		camera_translater = glm::translate(camera_translater, glm::vec3(-center_vertex.x, center_vertex.y, center_vertex.z));
		camera_rotater = glm::rotate(camera_rotater, glm::radians(camera_angle), glm::vec3(0.0, 1.0, 0.0));

		// 카메라 키보드 누르면 돌아가게
		if (is_Q_pressing && !is_P_pressed && !ball.is_clear)
		{
			/*if (is_P_pressed)
			{
			   camera_translater = glm::mat4(1.0f);
			   camera_translater = glm::translate(camera_translater, glm::vec3(ball.center_vertex.x, -ball.center_vertex.y+10.0f, -ball.center_vertex.z));
			}*/
			camera_angle += 3.0f;
			camera_rotater = glm::mat4(1.0f);
			camera_rotater = glm::rotate(camera_rotater, glm::radians(camera_angle), glm::vec3(0.0, 1.0, 0.0));
		}
		else if (is_E_pressing && !is_P_pressed && !ball.is_clear)
		{

			/*if (is_P_pressed)
			{
			   camera_translater = glm::mat4(1.0f);
			   camera_translater = glm::translate(camera_translater, glm::vec3(ball.center_vertex.x, -ball.center_vertex.y+10.0f, -ball.center_vertex.z));
			}*/
			camera_angle -= 3.0f;
			camera_rotater = glm::mat4(1.0f);
			camera_rotater = glm::rotate(camera_rotater, glm::radians(camera_angle), glm::vec3(0.0, 1.0, 0.0));
		}
		else if (is_M_pressed && !ball.is_clear) // 설명으로 카메라 고정
		{
			camera_angle = 180.0f;
			camera_rotater = glm::mat4(1.0f);
			camera_rotater = glm::rotate(camera_rotater, glm::radians(camera_angle), glm::vec3(0.0, 1.0, 0.0));
			camera_translater = glm::mat4(1.0f);
			camera_translater = glm::translate(camera_translater, glm::vec3(0.0f, -60.0f, 25.0f));
		}



		//cout << "camera x :" << center_vertex.x << " camera y : " << center_vertex.y << " camera z :" << center_vertex.z << endl;
		//cout << "angle:" << camera_angle << endl;

		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
		view = view * camera_rotater * camera_translater;
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	}
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::mat4 view;
	glm::mat4 camera_translater;
	glm::mat4 camera_rotater;
	glm::vec4 center_vertex;
	//카메라 좌표
	float camera_x;
	float camera_y;
	float camera_z;
	//카메라 움직일때 더해주는 좌표(이동량)
	float camera_move_x;
	float camera_move_y;
	float camera_move_z;
	// 카메라 회전 각도
	float camera_angle;
	// 진행 방향에 따른 카메라 초기 각도
	float cam_angle_by_dir;

	//카메라 공전
	bool is_Q_pressing;
	bool is_E_pressing;
	bool is_Q_up;
	bool is_E_up;

	//카메라 공 following 모드
	bool is_P_pressed;

	// 설명(튜토리얼)으로 카메라 고정
	bool is_M_pressed;
	bool is_M_up;
};


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid Timerfunc(int value);

GLuint compile_shaders(const char* vertex, const char* frag);
char* filetobuf(const char* file);
void drawCube();
void drawSphere();
void drawTutoTextureRect(const char* image_file);
void drawLavaTextureRect(const char* image_file);

void checkCollide(C_PlayerBall* sphere, C_Block* cube, float radian, float half_cm);
void moveByKeyboard();
void makeBlock(GLuint shaderprogramID, int objColorLocation);


C_Camera camera{};
C_Block block[BLOCKNUMBER];



int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정  
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("BouncingBall#3D"); // 윈도우 생성
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	srand(time(nullptr));
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(100, Timerfunc, 1);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작 
	return 0;
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		if (ball.is_on_rocket_front || ball.is_on_rocket_left || ball.is_on_rocket_right)
		{
			ball.is_stop = true;
			ball.is_on_rocket_front = false;
			ball.is_on_rocket_left = false;
			ball.is_on_rocket_right = false;
		}
	}
	switch (key) {
	case 'w':
		is_W_pressed = true;
		//glutPostRedisplay();
		break;
	case 'a':
		is_A_pressed = true;
		//glutPostRedisplay();
		break;
	case 's':
		is_S_pressed = true;
		//glutPostRedisplay();
		break;
	case 'd':
		is_D_pressed = true;
		//glutPostRedisplay();
		break;
	case 'Q': // 카메라 좌로 회전
	case 'q':
		camera.is_Q_pressing = true;
		camera.is_Q_up = false;
		//camera.is_E_pressing = false;
		break;
	case 'E': // 카메라 우로 회전
	case 'e':
		//camera.is_Q_pressing = false;
		camera.is_E_pressing = true;
		camera.is_E_up = false;
		break;
	case 'P':
	case 'p':
		if (!camera.is_P_pressed)
			camera.is_P_pressed = true;
		else
			camera.is_P_pressed = false;

		break;
	case 'M': // 설명(튜토리얼) 화면으로 카메라 고정
	case 'm':
		camera.is_M_pressed = true;
		camera.is_M_up = false;
		break;
	case '0': // 치트
		if (block_cheat_index <= 70)
		{
			if (block_cheat_index == 35)
				block_cheat_index += 10;
			else if (block_cheat_index == 60)
				block_cheat_index += 12;
			else
				block_cheat_index += 5;

			ball.pos_x = block_pos[block_cheat_index].x;
			ball.pos_y = block_pos[block_cheat_index].y + 1.0f;
			ball.pos_z = block_pos[block_cheat_index].z;
		}
		break;

	case 27:
		glutExit();
		break;
	}

}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		is_W_pressed = false;
		break;
	case 'a':
		is_A_pressed = false;
		break;
	case 's':
		is_S_pressed = false;
		break;
	case 'd':
		is_D_pressed = false;
		break;
	case 'Q': // 카메라 좌로 회전
	case 'q':
		camera.is_Q_pressing = false;
		camera.is_Q_up = true;
		break;
	case 'E': // 카메라 우로 회전
	case 'e':
		camera.is_E_pressing = false;
		camera.is_E_up = true;
		break;
	case 'M':
	case 'm':
		camera.is_M_pressed = false;
		camera.is_M_up = true;
		break;
	}

}

GLvoid Timerfunc(int value)
{
	moveByKeyboard();

	if (ball.is_stop)
	{
		ball.pos_y -= ball.bounce_speed;
		ball.bounce_speed += GRAVITY;
	}
	else if (ball.is_on_rocket_front)
	{
		ball.pos_z += 0.5f;
	}
	else if (ball.is_on_rocket_left)
	{
		ball.pos_x -= 0.5f;
	}
	else if (ball.is_on_rocket_right)
	{
		ball.pos_x += 0.5f;
	}
	else
	{
		ball.pos_y += ball.bounce_speed;
		ball.bounce_speed -= GRAVITY;
	}
	for (int i = 0; i < BLOCKNUMBER; i++)
	{
		if (block[i].type == MOVING_RL || block[i].type == MOVING_FB || block[i].type == UP)
			block[i].Move();
		if (!block[i].is_broken)
		{
			checkCollide(&ball, &block[i], ball.radian, block[i].half_cm);
		}
	}

	if (ball.pos_y < -35.0f)
	{
		// 블록 치트 리셋
		//block_cheat_index = 60;
		block_cheat_index -= 5;
		ball.pos_x = -ball.strat_pos_x;
		ball.pos_z = ball.start_pos_z;
		ball.pos_y = ball.start_pos_y + 1;
		ball.is_regen = false;

	}

	if (ball.pos_y > -35.0f && ball.pos_y <= -10.0f) {
		camera.is_P_pressed = true;
		camera.is_E_pressing = false;
		ball.is_regen = true;
	}

	glutPostRedisplay();
	glutTimerFunc(50, Timerfunc, 1);
}
GLuint shaderprogramID;
GLuint programID2;

GLvoid drawScene() // 콜백 함수: 출력
{
	if (!is_shader1_init)
	{
		shaderprogramID = compile_shaders("vertex3.glsl", "fragment2.glsl");
		is_shader1_init = true;
	}
	glUseProgram(shaderprogramID);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 바탕색을 'blue'로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	int lightPosLocation = glGetUniformLocation(shaderprogramID, "lightPos");
	int lightColorLocation = glGetUniformLocation(shaderprogramID, "lightColor");
	int objColorLocation = glGetUniformLocation(shaderprogramID, "objectColor");
	int viewPosLocation = glGetUniformLocation(shaderprogramID, "viewPos");
	int alpaPosLocation = glGetUniformLocation(shaderprogramID, "alpa");


	glUniform3f(lightPosLocation, camera.camera_move_x, 1000.0, camera.camera_move_z);
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	glUniform3f(viewPosLocation, camera.camera_x, 1.0, camera.camera_z);
	glUniform3f(objColorLocation, 1.0, 0.0, 0.0);
	glUniform1f(alpaPosLocation, 1.0f);

	camera.CameraSet(shaderprogramID, ball);
	ball.Move(shaderprogramID);
	drawSphere();

	// 블록 그리기
	makeBlock(shaderprogramID, objColorLocation);



	//설명(튜토리얼) 텍스쳐
	if (!is_shader2_init)
	{
		programID2 = compile_shaders("22vs.glsl", "22fs.glsl");
		is_shader2_init = true;
	}
	glUseProgram(programID2);
	camera.CameraSet(programID2, ball);
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 tex_translater = glm::mat4(1.0f);
	glm::mat4 tex_rotater = glm::mat4(1.0f);
	glm::mat4 tex_scaler = glm::mat4(1.0f);


	int modelLoc = glGetUniformLocation(programID2, "model");
	//tex_translater = glm::translate(tex_translater, glm::vec3(0.0f, -20.0f, -25.0f));
	tex_translater = glm::translate(tex_translater, glm::vec3(2.0f, 55.0f, -25.0f));
	tex_rotater = glm::rotate(tex_rotater, glm::radians(-30.0f), glm::vec3(1, 0, 0));
	tex_scaler = glm::scale(tex_scaler, glm::vec3(70.0f, 70.0f, 70.0f));
	TR *= tex_rotater * tex_translater * tex_scaler;
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(TR));

	if (camera.is_M_pressed)
		drawTutoTextureRect("back_background1.bmp");

	if (ball.is_clear)
	{
		modelLoc = glGetUniformLocation(programID2, "model");
		TR = glm::mat4(1.0f);
		tex_translater = glm::mat4(1.0f);
		tex_rotater = glm::mat4(1.0f);
		glm::mat4 tex_rotater1 = glm::mat4(1.0f);

		tex_scaler = glm::mat4(1.0f);


		//86,3,362
		tex_translater = glm::translate(tex_translater, glm::vec3(-86.0f, -367.0f, 0.0f));
		//tex_translater = glm::translate(tex_translater, glm::vec3(0.0f, 0.0f, 0.0f));

		tex_rotater = glm::rotate(tex_rotater, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		//tex_rotater1 = glm::rotate(tex_rotater, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		tex_scaler = glm::scale(tex_scaler, glm::vec3(100.0f, 100.0f, 100.0f));
		TR *= tex_rotater * tex_translater * tex_scaler;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(TR));
		drawLavaTextureRect("firework.bmp");


		// 아래 폭죽
		//modelLoc = glGetUniformLocation(programID2, "model");
		//TR = glm::mat4(1.0f);
		//tex_translater = glm::mat4(1.0f);
		//tex_rotater = glm::mat4(1.0f);
		//tex_rotater1 = glm::mat4(1.0f);

		//tex_scaler = glm::mat4(1.0f);

		////86,3,362
		//tex_translater = glm::translate(tex_translater, glm::vec3(-86.0f, -350.0f, 0.0f));
		////tex_translater = glm::translate(tex_translater, glm::vec3(0.0f, 0.0f, 0.0f));

		//tex_rotater = glm::rotate(tex_rotater, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		////tex_rotater1 = glm::rotate(tex_rotater, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		//tex_scaler = glm::scale(tex_scaler, glm::vec3(50.0f, 50.0f, 50.0f));
		//TR *= tex_rotater * tex_translater * tex_scaler;
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(TR));

		drawLavaTextureRect("firework.bmp");
	}

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}

void drawCube()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendColor(0.2f, 0.5f, 0.7f, 0.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint vao, vbo;


	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexSquare), vertexSquare, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisable(GL_BLEND);
}

void drawSphere()
{
	glEnable(GL_DEPTH_TEST);

	GLuint vao, vbo[2];


	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);


	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, sphere_vertex_size);
}

void drawTutoTextureRect(const char* image_name)
{
	unsigned int VBO[2], VAO[2], EBO;
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	//첫번째 버텍스 데이터
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertexData1), RectVertexData1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//두번째 버텍스 데이터
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertexData2), RectVertexData2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//---texture1
	unsigned int texture1, texture2;
	BITMAPINFO* bmp;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	if (!is_tuto_init)
	{
		tuto_image1 = stbi_load(image_name, &widthImage, &heightImage, &numberOfChannel, 0);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, tuto_image1);
	//---texture2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	if (!is_tuto_init)
	{
		tuto_image2 = stbi_load(image_name, &widthImage, &heightImage, &numberOfChannel, 0);
		is_tuto_init = true;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, tuto_image2);

	glBindVertexArray(VAO[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(VAO[1]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void drawLavaTextureRect(const char* image_name)
{
	unsigned int VBO[2], VAO[2], EBO;
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	//첫번째 버텍스 데이터
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertexData1), RectVertexData1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//두번째 버텍스 데이터
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertexData2), RectVertexData2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//---texture1
	unsigned int texture1, texture2;
	BITMAPINFO* bmp;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	if (!is_lava_init)
	{
		lava_image1 = stbi_load(image_name, &widthImage, &heightImage, &numberOfChannel, 0);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, lava_image1);
	//---texture2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	if (!is_lava_init)
	{
		lava_image2 = stbi_load(image_name, &widthImage, &heightImage, &numberOfChannel, 0);
		is_lava_init = true;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, lava_image2);

	glBindVertexArray(VAO[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(VAO[1]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void drawTextureTri(const char* image_name) {
	unsigned int VBO[1], VAO[1], EBO;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	//첫번째 버텍스 데이터
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertexData), TriangleVertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//---texture1
	unsigned int texture1, texture2;
	BITMAPINFO* bmp;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image_name, &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


	glBindVertexArray(VAO[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void checkCollide(C_PlayerBall* sphere, C_Block* cube, float radian, float half_cm)
{
	float range_of_y = 1.0f;
	float range_of_xz = half_cm + 0.5f;//충돌범위 조절하는 파라미터
	float min_range_x = cube->center_vertex.x - range_of_xz;
	float max_range_x = cube->center_vertex.x + range_of_xz;
	float min_range_z = cube->center_vertex.z - range_of_xz;
	float max_range_z = cube->center_vertex.z + range_of_xz;
	float min_range_y = cube->center_vertex.y;
	if (ball.is_on_jump_block)
		range_of_y = 1.5f;
	float max_range_y = cube->center_vertex.y + half_cm + radian + range_of_y;

	if ((min_range_x<sphere->center_vertex.x && max_range_x>sphere->center_vertex.x) &&
		(min_range_z<sphere->center_vertex.z && max_range_z>sphere->center_vertex.z) &&
		(min_range_y<sphere->center_vertex.y && max_range_y>sphere->center_vertex.y))
	{
		if (sphere->is_stop)
			sphere->is_stop = false;
		//cout << "is Collide x :" << sphere.x << " y : " << sphere.y << " z : " << sphere.z << endl;
		if (cube->is_dir_change)
		{
			sphere->dir = cube->dir;
		}

		if (cube->is_save_point)
		{
			cube->is_saved = true;
			sphere->strat_pos_x = cube->center_vertex.x;
			sphere->start_pos_y = cube->center_vertex.y;
			sphere->start_pos_z = cube->center_vertex.z;
		}

		ball.bounce_speed = ball.start_bounce_speed;
		if (cube->type == DOUBLEJUMP)
		{
			ball.is_on_jump_block = true;
			ball.bounce_speed *= 1.45f;
		}
		if (cube->type == BROKEN)
		{
			cube->is_broken = true;
			//cout << "broken" << endl;
		}
		if (cube->type == ROCKET_FRONT)
		{
			ball.is_on_rocket_front = true;
		}
		if (cube->type == ROCKET_LEFT)
		{
			ball.is_on_rocket_left = true;
		}
		if (cube->type == ROCKET_RIGHT)
		{
			ball.is_on_rocket_right = true;
		}
		if (cube->type == UP) {
			if (cube->is_up == false)
				cube->is_up = true;
		}
		if (cube->type == CLEAR)
		{
			ball.is_clear = true;
		}
	}
}

void moveByKeyboard()
{
	if (is_W_pressed && !ball.is_clear)
	{
		if (ball.dir == FRONT)
		{
			ball.pos_z += 0.3f;
		}
		else if (ball.dir == RIGHT)
		{
			ball.pos_x += 0.3f;
		}
		else if (ball.dir == LEFT)
		{
			ball.pos_x -= 0.3f;
		}
	}
	if (is_A_pressed && !ball.is_clear)
	{
		if (ball.dir == FRONT)
		{
			ball.pos_x -= 0.3f;
		}
		else if (ball.dir == RIGHT)
		{
			ball.pos_z += 0.3f;
		}
		else if (ball.dir == LEFT)
		{
			ball.pos_z -= 0.3f;
		}
	}
	if (is_S_pressed && !ball.is_clear)
	{
		if (ball.dir == FRONT)
		{
			ball.pos_z -= 0.3f;
		}
		else if (ball.dir == RIGHT)
		{
			ball.pos_x -= 0.3f;
		}
		else if (ball.dir == LEFT)
		{
			ball.pos_x += 0.3f;
		}
	}
	if (is_D_pressed && !ball.is_clear)
	{
		if (ball.dir == FRONT)
		{
			ball.pos_x += 0.3f;
		}
		else if (ball.dir == RIGHT)
		{
			ball.pos_z -= 0.3f;
		}
		else if (ball.dir == LEFT)
		{
			ball.pos_z += 0.3f;
		}
	}
}

void makeBlock(GLuint shaderprogramID, int objColorLocation)
{
	// 블록 그리기
	for (int i = 0; i < BLOCKNUMBER; i++) {
		// 방향 전환 블록 설정
		if (i == 5 || i == 15 || i == 35 || i == 50)
		{
			block[i].is_dir_change = true;
			block[i].dir = RIGHT;
		}
		else if (i == 0 || i == 10 || i == 20 || i == 30 || i == 45 || i == 55)
		{
			block[i].is_dir_change = true;
			block[i].dir = FRONT;
		}
		else if (i == 25 || i == 52) {
			block[i].is_dir_change = true;
			block[i].dir = LEFT;
		}
		//
		//세이브 포인트 블럭지정
		if (i == 0 || i == 10 || i == 20 || i == 30 || i == 45 || i == 55 || i == 60)
		{
			block[i].is_save_point = true;
		}


		if (i == 31 || i == 32 || i == 33 || i == 34 || i == 40 || i == 41 || i == 42 || i == 43 || i == 44 || i == 63 || i == 67 || i == 68 || i == 69)
		{
			if (ball.is_regen)
			{
				block[i].is_broken = false;
			}

			if (!block[i].is_broken)
				block[i].Set(shaderprogramID, block_pos[i], BROKEN);
		}
		else if (i == 21 || i == 22 || i == 23 || i == 24 || i == 25 || i == 26 || i == 28 || i == 29 || i == 52 || i == 54 || i == 57 || i == 64) {
			block[i].Set(shaderprogramID, block_pos[i], DOUBLEJUMP);
		}
		else if (i == 46 || i == 48 || i == 59 || i == 62 || i == 71)
		{
			block[i].Set(shaderprogramID, block_pos[i], ROCKET_FRONT);
		}
		else if (i == 51 || i == 70) {
			block[i].Set(shaderprogramID, block_pos[i], ROCKET_RIGHT);
		}
		else if (i == 53 || i == 61) {
			block[i].Set(shaderprogramID, block_pos[i], ROCKET_LEFT);
		}
		else if (i == 56 || i == 65) {
			block[i].Set(shaderprogramID, block_pos[i], MOVING_RL);
		}
		else if (i == 58 || i == 66) {
			block[i].Set(shaderprogramID, block_pos[i], MOVING_FB);
		}
		else if (i == 72) {
			block[i].Set(shaderprogramID, block_pos[i], UP);
		}
		else if (i == 73) {
			block[i].Set(shaderprogramID, block_pos[i], CLEAR);

		}
		else {
			block[i].Set(shaderprogramID, block_pos[i], NORMAL);
		}


		if (!block[i].is_broken)
			drawCube();
	}
}
GLuint compile_shaders(const char* vertex, const char* frag)

{

	GLchar* vertexsource, * fragmentsource;

	//GLuint vertexshader, fragmentshader; // 세이더

	vertexsource = filetobuf(vertex);

	fragmentsource = filetobuf(frag);

	//--- 버텍스 세이더 객체 만들기

	//vertexshader = glCreateShader(GL_VERTEX_SHADER);



	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar * *)& vertexsource, 0);

	glCompileShader(vertexShader);

	GLint result;

	GLchar errorLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if (!result)

	{

		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);

		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;

		return false;

	}

	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 세이더 코드를 세이더 객체에 넣기: GL로 보내진다.

	glShaderSource(fragmentShader, 1, (const GLchar * *)& fragmentsource, 0);

	// 프래그먼트 세이더 컴파일

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result)

	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);

		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;

		return false;

	}


	GLuint ShaderProgramID = glCreateProgram(); //--- 세이더 프로그램 만들기

	glAttachShader(ShaderProgramID, vertexShader); // 세이더 프로그램에 버텍스 세이더 붙이기

	glAttachShader(ShaderProgramID, fragmentShader); // 세이더 프로그램에 프래그먼트 세이더 붙이기

	glLinkProgram(ShaderProgramID); // 세이더 프로그램 링크하기

	glDeleteShader(vertexShader); // 세이더 프로그램에 링크하여 세이더 객체 자체는 삭제 가능

	glDeleteShader(fragmentShader);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // 세이더가 잘 연결되었는지 체크하기

	if (!result) {

		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);

		cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;

		return false;

	}

	glUseProgram(ShaderProgramID); //--- 만들어진 세이더 프로그램 사용하기

	// 여러 개의 프로그램 만들 수 있고, 특정 프로그램을 사용하려면

	// glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.

	// 사용하기 직전에 호출할 수 있다.

	return ShaderProgramID;


}
char* filetobuf(const char* file)
{
	FILE* fptr;

	long length;

	char* buf;

	fptr = fopen(file, "rb"); // Open file for reading

	if (!fptr) // Return NULL on failure
		return NULL;

	fseek(fptr, 0, SEEK_END); // Seek to the end of the file

	length = ftell(fptr); // Find out how many bytes into the file we are

	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator

	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file

	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer

	fclose(fptr); // Close the file

	buf[length] = 0; // Null terminator

	return buf; // Return the buffer
}