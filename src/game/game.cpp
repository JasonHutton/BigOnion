#include "game.h"

Game::Game()
{

}

void Game::init(BOEngine* engine)
{
	std::cout << "Game init" << std::endl;

	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0, -9.8, 0));	//gravity on Earth


	modelShader = new Shader("src/engine/graphic/shader/model_loading.vs", "src/engine/graphic/shader/model_loading.fs");

	// create suit man
	suitManModel = new Model("src/game/assets/nanosuit/nanosuit.obj", modelShader);

	suitMan = new GameObject("SuitMan");
	suitMan->addComponent(new RenderComponent(&suitManModel->shaderAttribute)); // connect object - model
	suitMan->transform.setPosition(Vector3f(0.0f, 10.f, 0.0f));
	suitMan->transform.setScale(Vector3f(0.2f, 0.2f, 0.2f));
	suitMan->transform.setRotation(Vector3f(3.14f, 3.14f, 0.0f));

	suitMan->addComponent(new RigidBodyComponent(addCylinder(0.75, 1.5, 0.25, 0, 20, 0, 1.0))); // connect object - rigibody
	engine->gameWorld.addGameObject(suitMan); // maybe auto register?

	// create ground
	groundModel = new Model("src/game/assets/ground/plane.obj", modelShader);
	ground = new GameObject("Ground");
	ground->addComponent(new RenderComponent(&groundModel->shaderAttribute));
	ground->addComponent(new RigidBodyComponent(addPlane(0, -3.25, 0)));
	engine->gameWorld.addGameObject(ground);

	ground->transform.setPosition(Vector3f(0, -3.25, 0));
	ground->transform.setScale(Vector3f(100.0f, 1.0f, 100.0f));

	// create box
	boxModel = new Model("src/game/assets/box/cube.obj", modelShader);
	box = new  GameObject("Box");
	box->addComponent(new RenderComponent(&boxModel->shaderAttribute));
	box->addComponent(new RigidBodyComponent(addCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0)));
	engine->gameWorld.addGameObject(box);

	box->transform.setPosition(Vector3f(5.0, 30, 0));
	box->transform.setScale(2.5);

	// create box without physics
	boxWithoutBtModel = new Model("src/game/assets/box/cube.obj", modelShader);
	boxWithoutBt = new  GameObject("boxWithoutBt");
	boxWithoutBt->addComponent(new RenderComponent(&boxWithoutBtModel->shaderAttribute));
	// boxWithoutBt->addComponent(new RigidBodyComponent(addCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0)));
	engine->gameWorld.addGameObject(boxWithoutBt);

	boxWithoutBt->transform.setPosition(Vector3f(0.0, 0.2, -2));
	boxWithoutBt->transform.setScale(1.5);

}

void Game::updateWithDelta(float deltaTime)
{


	Vector3f p2 = boxWithoutBt->transform.getPosition();
	p2.z -= 0.01f;
	// p2.x -= 0.01f;
	//boxWithoutBt->transform.setPosition(p2);


	Vector3f r = box->transform.getRotation();
	box->transform.setRotation(r);

	Vector3f r2 = boxWithoutBt->transform.getRotation();
	r2.z -= 0.01f;
	r2.x = 1.01f;
	boxWithoutBt->transform.setRotation(r2);

	Vector3f r3 = suitMan->transform.getRotation();
	r3.z -= 0.01f;
	r3.x = 1.01f;
	// suitMan->transform.setRotation(r3);

	return;
}

void Game::render(BOEngine* engine)
{
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// don't forget to enable shader before setting uniforms
	modelShader->use();

	int scrWidth = 10; //TODO get from window
	int scrHeight = 8; //TODO get from window

	glfwGetWindowSize(engine->window, &scrWidth, &scrHeight);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(engine->camera.Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	glm::mat4 view = engine->camera.GetViewMatrix();

	modelShader->setMat4("projection", projection);
	modelShader->setMat4("view", view);

	groundModel->Draw();
	boxModel->Draw();
	boxWithoutBtModel->Draw();
	suitManModel->Draw();

	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE) {
		}
		else if (bodies[i]->getCollisionShape()->getShapeType() == BOX_SHAPE_PROXYTYPE) {
			//glm::mat4 cubeModel = glm::mat4(1.0f);
			//btTransform transform;
			//bodies[i]->getMotionState()->getWorldTransform(transform);	//get the transform
			//transform.getOpenGLMatrix(glm::value_ptr(cubeModel));

			//btVector3 scale = ((btBoxShape*)bodies[i]->getCollisionShape())->getHalfExtentsWithoutMargin();
			//cubeModel = glm::scale(cubeModel, glm::vec3(2 * scale.getX(), 2 * scale.getY(), 2 * scale.getZ()));

			//boxModel->shaderAttribute.setMat4("model", cubeModel);
			//boxModel->Draw();
		}
		else if (bodies[i]->getCollisionShape()->getShapeType() == CYLINDER_SHAPE_PROXYTYPE) {
			// render the loaded model

						//}
			//glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 10, 0));
			//modelMatrix = glm::rotate(modelMatrix, 3.14f, glm::vec3(1.0f, 0.0f, 0.0f));
			//modelMatrix = glm::rotate(modelMatrix, 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));
			//modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			//modelMatrix = glm::scale(modelMatrix, suitMan->transform.getScale().getGlmVec3());

		}

	}


	world->stepSimulation(1 / 60.0);
}

btRigidBody* Game::addCube(float width, float height, float depth, float x, float y, float z, float mass)
{
	btTransform t;	//position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));	//put it to x,y,z coordinates
	btBoxShape* box = new btBoxShape(btVector3(width, height, depth));
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		box->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself
	world->addRigidBody(body);	//and let the world know about it
	bodies.push_back(body);	//to be easier to clean, I store them a vector
	return body;
}

btRigidBody* Game::addPlane(float x, float y, float z) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);
	world->addRigidBody(body);
	bodies.push_back(body);
	return body;
}

btRigidBody* Game::addCylinder(float width, float height, float depth, float x, float y, float z, float mass) {
	btTransform t;	//position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));	//put it to x,y,z coordinates
	btCylinderShape* cylinder = new btCylinderShape(btVector3(width, height, depth));
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		cylinder->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself
	world->addRigidBody(body);	//and let the world know about it
	bodies.push_back(body);	//to be easier to clean, I store them a vector
	return body;
}