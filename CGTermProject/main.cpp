#include "loadObj.cpp"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GRAVITY 0.03
#define BLOCKNUMBER 74

using namespace std;

// ���� �Ұ�
// 1.ī�޶�ϼ� : ȸ�� �� ���¿��� Ű���� ������ �� �ڷ� �ٽ� ����//DONE
// 2. ������ �� ����� : 2�� ���� ���, ������ ������ ���, ������ ���� ���� ���(�Է� ������ �� ���ư�), �����̴� ���//DONE
// 3. �� ����� : ��ġ��(vec3) ��� vector -> �ε������� ���,�����ۺ�� �־��ֱ�
// 4. ���̺� ����Ʈ : �׾��� �� ��Ȱ ��ġ ���� -> ���̺� ����Ʈ�� ǳ�� ����
// *�߰�: �����緯 ������ ���� ���̱�
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
glm::vec3(34,0,150),glm::vec3(40,-3,150),glm::vec3(46,-5,153),glm::vec3(53,-7,150),glm::vec3(58,-6,145),glm::vec3(66,-6,146),//40//��
glm::vec3(40,3,150),glm::vec3(46,5,153),glm::vec3(53,5,150),glm::vec3(58,3,145),//44//��
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

// ���� ����
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
// ��� ���� �ؽ��� �ѹ��� �ʱ�ȭ
bool is_tuto_init = false;
unsigned char* tuto_image1;
unsigned char* tuto_image2;
// �ٴ�(���) �ؽ��� �ѹ��� �ʱ�ȭ
bool is_lava_init = false;
unsigned char* lava_image1;
unsigned char* lava_image2;
// Ŭ���� ȭ�� �ѹ��� �ʱ�ȭ
bool is_clear_init = false;
unsigned char* clear_image1;
unsigned char* clear_image2;
// ���̴� �ѹ��� �ʱ�ȭ
bool is_shader1_init = false;
bool is_shader2_init = false;

//ġƮ ��� �ε���
int block_cheat_index = 0;

//obj ���� �ҷ����°�
int sphere_vertex_size = loadObj("Sphere.obj");

//�ؽ��� ����
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
	//���� ��ġ
	float pos_x;
	float pos_y;
	float pos_z;

	//���� ������//
	float radian;

	//�� ���� ��ġ(�� ��ġ)
	float strat_pos_x;
	float start_pos_y;
	float start_pos_z;

	// �� �⺻ Ƣ���(y��) �ӵ�
	float start_bounce_speed;
	// �� Ƣ��� �ӵ�
	float bounce_speed;

	glm::mat4 ball_translater;
	glm::mat4 TR;
	glm::mat4 ball_scaler;
	glm::vec4 center_vertex;

	// ���� 2�� ���� ��ϰ� �浹�ߴ���
	bool is_on_jump_block;
	// ���� Ư�� ���� ���� ��ϰ� �浹�ߴ���
	bool is_on_rocket_front;
	bool is_on_rocket_left;
	bool is_on_rocket_right;
	// ���Ϻ�� ������ ���߱�
	bool is_stop;
	//��ġ ���� �迭
	glm::vec3 Vpos;

	//��Ƴ�����
	bool is_regen;

	// ���� �ٿ���ϰ� �ִ���(���� ��ϰ� �浹 �� �ٿ�� ����)
	bool is_bouncing;

	//Ŭ���� ��ϰ� �浹
	bool is_clear;

	// ���� ����
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
	// �����̴� ��� �̵����
	glm::mat4 moving_translater;
	glm::mat4 TR;
	glm::vec4 center_vertex;

	//�� ���� 1cm
	float half_cm = 0.5f;//block half Cm
	// �� Ÿ��
	BlockType type;
	// �μ��� ��� ó��
	bool is_broken;
	// ��ġ ���� ����
	glm::vec3 vPos;
	// MOVING Ÿ���� �� ��� �̵���
	float dx;
	float dy;
	float dz;
	// MOVING Ÿ���� �� ��� speed
	float speed;

	// MOVING Ÿ���϶� ��� �̵�����
	bool is_right;
	bool is_left;
	bool is_front;
	bool is_back;
	bool is_up;
	//���̺� ����Ʈ ����
	bool is_save_point;
	// ���� ���̺� �Ǿ�����
	bool is_saved;
	// ���� ��ȯ ����
	bool is_dir_change;
	// �浹�� ���� ���� ���� ����
	Dir dir;
};


class C_Camera
{
public:
	C_Camera()
	{
		//ī�޶� ��ǥ
		camera_x = 0.0f;
		camera_y = 20.0f;
		camera_z = 20.0f;
		//ī�޶� �����϶� �����ִ� ��ǥ(�̵���)
		camera_move_x = 0.0f;
		camera_move_y = 0.0f;
		camera_move_z = 0.0f;
		is_Q_pressing = false;
		is_E_pressing = false;
		is_Q_up = false;
		is_E_up = false;
		is_P_pressed = false;
		//ī�޶� ȸ������
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

		//ī�޶� �Ķ����
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
		// ī�޶� �� �ڿ� ����
		if (is_P_pressed && !ball.is_clear)
		{
			if (ball.dir == RIGHT)
			{
				center_vertex.x = ball.center_vertex.x - 10.0f;
				center_vertex.y = -ball.center_vertex.y + 10.0f; // �� Ƣ��°� ���� ���󰡰�
				center_vertex.z = -ball.center_vertex.z;
			}
			else if (ball.dir == LEFT)
			{
				center_vertex.x = ball.center_vertex.x + 10.0f;
				center_vertex.y = -ball.center_vertex.y + 10.0f; // �� Ƣ��°� ���� ���󰡰�
				center_vertex.z = -ball.center_vertex.z;
			}
			else
			{
				center_vertex.x = ball.center_vertex.x;
				center_vertex.y = -ball.center_vertex.y + 10.0f; // �� Ƣ��°� ���� ���󰡰�
				center_vertex.z = -ball.center_vertex.z - 10.0f;
			}
		}
		else // ������ ����
		{
			center_vertex.x = ball.center_vertex.x;
			center_vertex.y = 0.0f;
			center_vertex.z = -ball.center_vertex.z;
		}
		//camera_translater = glm::translate(camera_translater, glm::vec3(camera_move_x, camera_move_y, camera_move_z));



		camera_translater = glm::translate(camera_translater, glm::vec3(-center_vertex.x, center_vertex.y, center_vertex.z));
		camera_rotater = glm::rotate(camera_rotater, glm::radians(camera_angle), glm::vec3(0.0, 1.0, 0.0));

		// ī�޶� Ű���� ������ ���ư���
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
		else if (is_M_pressed && !ball.is_clear) // �������� ī�޶� ����
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
	//ī�޶� ��ǥ
	float camera_x;
	float camera_y;
	float camera_z;
	//ī�޶� �����϶� �����ִ� ��ǥ(�̵���)
	float camera_move_x;
	float camera_move_y;
	float camera_move_z;
	// ī�޶� ȸ�� ����
	float camera_angle;
	// ���� ���⿡ ���� ī�޶� �ʱ� ����
	float cam_angle_by_dir;

	//ī�޶� ����
	bool is_Q_pressing;
	bool is_E_pressing;
	bool is_Q_up;
	bool is_E_up;

	//ī�޶� �� following ���
	bool is_P_pressed;

	// ����(Ʃ�丮��)���� ī�޶� ����
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



int main(int argc, char** argv) // ������ ����ϰ� �ݹ��Լ� ����  
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // �������� ũ�� ����
	glutCreateWindow("BouncingBall#3D"); // ������ ����
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
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
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
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
	case 'Q': // ī�޶� �·� ȸ��
	case 'q':
		camera.is_Q_pressing = true;
		camera.is_Q_up = false;
		//camera.is_E_pressing = false;
		break;
	case 'E': // ī�޶� ��� ȸ��
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
	case 'M': // ����(Ʃ�丮��) ȭ������ ī�޶� ����
	case 'm':
		camera.is_M_pressed = true;
		camera.is_M_up = false;
		break;
	case '0': // ġƮ
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
	case 'Q': // ī�޶� �·� ȸ��
	case 'q':
		camera.is_Q_pressing = false;
		camera.is_Q_up = true;
		break;
	case 'E': // ī�޶� ��� ȸ��
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
		// ��� ġƮ ����
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

GLvoid drawScene() // �ݹ� �Լ�: ���
{
	if (!is_shader1_init)
	{
		shaderprogramID = compile_shaders("vertex3.glsl", "fragment2.glsl");
		is_shader1_init = true;
	}
	glUseProgram(shaderprogramID);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // �������� 'blue'�� ����
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

	// ��� �׸���
	makeBlock(shaderprogramID, objColorLocation);



	//����(Ʃ�丮��) �ؽ���
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


		// �Ʒ� ����
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

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) // �ݹ� �Լ�: �ٽ� �׸��� 
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

	//ù��° ���ؽ� ������
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertexData1), RectVertexData1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//�ι�° ���ؽ� ������
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

	//ù��° ���ؽ� ������
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertexData1), RectVertexData1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//�ι�° ���ؽ� ������
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

	//ù��° ���ؽ� ������
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
	float range_of_xz = half_cm + 0.5f;//�浹���� �����ϴ� �Ķ����
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
	// ��� �׸���
	for (int i = 0; i < BLOCKNUMBER; i++) {
		// ���� ��ȯ ��� ����
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
		//���̺� ����Ʈ ������
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

	//GLuint vertexshader, fragmentshader; // ���̴�

	vertexsource = filetobuf(vertex);

	fragmentsource = filetobuf(frag);

	//--- ���ؽ� ���̴� ��ü �����

	//vertexshader = glCreateShader(GL_VERTEX_SHADER);



	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar * *)& vertexsource, 0);

	glCompileShader(vertexShader);

	GLint result;

	GLchar errorLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if (!result)

	{

		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);

		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;

		return false;

	}

	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ڵ带 ���̴� ��ü�� �ֱ�: GL�� ��������.

	glShaderSource(fragmentShader, 1, (const GLchar * *)& fragmentsource, 0);

	// �����׸�Ʈ ���̴� ������

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result)

	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);

		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;

		return false;

	}


	GLuint ShaderProgramID = glCreateProgram(); //--- ���̴� ���α׷� �����

	glAttachShader(ShaderProgramID, vertexShader); // ���̴� ���α׷��� ���ؽ� ���̴� ���̱�

	glAttachShader(ShaderProgramID, fragmentShader); // ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�

	glLinkProgram(ShaderProgramID); // ���̴� ���α׷� ��ũ�ϱ�

	glDeleteShader(vertexShader); // ���̴� ���α׷��� ��ũ�Ͽ� ���̴� ��ü ��ü�� ���� ����

	glDeleteShader(fragmentShader);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ���̴��� �� ����Ǿ����� üũ�ϱ�

	if (!result) {

		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);

		cerr << "ERROR: shader program ���� ����\n" << errorLog << endl;

		return false;

	}

	glUseProgram(ShaderProgramID); //--- ������� ���̴� ���α׷� ����ϱ�

	// ���� ���� ���α׷� ���� �� �ְ�, Ư�� ���α׷��� ����Ϸ���

	// glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.

	// ����ϱ� ������ ȣ���� �� �ִ�.

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