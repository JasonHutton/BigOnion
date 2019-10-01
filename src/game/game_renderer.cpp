#include "game_renderer.h"


GameRenderer::GameRenderer()
{

}

void GameRenderer::init()
{
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0, -9.8, 0));	//gravity on Earth

	addPlane(0, -3.25, 0);

	addCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0);

	addCylinder(0.75, 1.5, 0.25, 0, 20, 0, 1.0);

	modelShader = Shader("src/engine/graphic/shader/model_loading.vs", "src/engine/graphic/shader/model_loading.fs");
	ourModel = Model("src/game/assets/nanosuit/nanosuit.obj");
	groundModel = Model("src/game/assets/ground/plane.obj");
	boxModel = Model("src/game/assets/box/cube.obj");
}

void GameRenderer::updateWithDelta(float deltaTime)
{
}

void GameRenderer::render(BOEngine* engine)
{
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// don't forget to enable shader before setting uniforms
	modelShader.use();

	int scrWidth = 10; //TODO get from window
	int scrHeight = 8; //TODO get from window

	glfwGetWindowSize(engine->window, &scrWidth, &scrHeight);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(engine->camera.Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	glm::mat4 view = engine->camera.GetViewMatrix();
	
	modelShader.setMat4("projection", projection);
	modelShader.setMat4("view", view);

	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE) {
			glm::mat4 planeModel = glm::mat4(1.0f);
			btTransform transform;
			bodies[i]->getMotionState()->getWorldTransform(transform);	//get the transform
			transform.getOpenGLMatrix(glm::value_ptr(planeModel));

			planeModel = glm::scale(planeModel, glm::vec3(100.0f, 1.0f, 100.0f));

			modelShader.setMat4("model", planeModel);
			groundModel.Draw(modelShader);
		}
		else if (bodies[i]->getCollisionShape()->getShapeType() == BOX_SHAPE_PROXYTYPE) {
			glm::mat4 cubeModel = glm::mat4(1.0f);
			btTransform transform;
			bodies[i]->getMotionState()->getWorldTransform(transform);	//get the transform
			transform.getOpenGLMatrix(glm::value_ptr(cubeModel));

			btVector3 scale = ((btBoxShape*)bodies[i]->getCollisionShape())->getHalfExtentsWithoutMargin();
			cubeModel = glm::scale(cubeModel, glm::vec3(2 * scale.getX(), 2 * scale.getY(), 2 * scale.getZ()));

			modelShader.setMat4("model", cubeModel);
			boxModel.Draw(modelShader);
		}
		else if (bodies[i]->getCollisionShape()->getShapeType() == CYLINDER_SHAPE_PROXYTYPE) {
			// render the loaded model
			glm::mat4 suitModel = glm::mat4(1.0f);
			btTransform transform;
			bodies[i]->getMotionState()->getWorldTransform(transform);	//get the transform
			transform.getOpenGLMatrix(glm::value_ptr(suitModel));

			suitModel = glm::scale(suitModel, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

			modelShader.setMat4("model", suitModel);
			ourModel.Draw(modelShader);
		}
	}

	world->stepSimulation(1 / 60.0);
}

btRigidBody* GameRenderer::addCube(float width, float height, float depth, float x, float y, float z, float mass)
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

btRigidBody* GameRenderer::addPlane(float x, float y, float z) {
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

btRigidBody* GameRenderer::addCylinder(float width, float height, float depth, float x, float y, float z, float mass) {
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