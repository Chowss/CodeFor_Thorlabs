#include "Paracurve.h"

bool Paracurve::sampling(float value, osg::Vec3Array* points, osg::Vec3Array* norms)
{
	//��ʼ������ϵ��
	int samplingNumber = 200;//��Բ�ܷ�Ϊ200������
	double radioStep = 0.05;//�뾶��������
	double radio = radioStep;//�뾶
	double radioMax = 5.0;//�������뾶
	double zMax = 5.0;//������zֵ
	double x, y, z;

	//Ԥ����
	std::vector<double> angleSin;//�����Ƕȶ�Ӧ������ֵ
	std::vector<double> angleCos;//�����Ƕȶ�Ӧ������ֵ
	angleSin.reserve(samplingNumber + 1);
	angleCos.reserve(samplingNumber + 1);
	double tmp = 3.14 * 2 / samplingNumber;
	for (int i = 0; i < samplingNumber; ++i)
	{
		angleSin.push_back(sin(i * tmp));
		angleCos.push_back(cos(i * tmp));
	}
	angleSin.push_back(sin(0));
	angleCos.push_back(cos(0));

	//�����涥�㴦����
	z = radio * radio * value;//�̶��뾶���zֵ
	osg::ref_ptr<osg::Vec3Array> vecPre = new osg::Vec3Array;//ǰһ��Բ���ϵĲ�����
	osg::ref_ptr<osg::Vec3Array> vecTmp = new osg::Vec3Array;//��������
	vecPre->reserve(samplingNumber + 1);
	vecTmp->reserve(samplingNumber + 1);
	for (int i = 0; i < samplingNumber + 1; ++i)
		vecTmp->push_back(osg::Vec3(radio * angleSin[i], radio * angleCos[i], z));

	vecPre->insert(vecPre->begin(), vecTmp->begin(), vecTmp->end());

	//������ת���������ζ���
	for (int i = 0; i < samplingNumber; ++i)
	{
		points->push_back(vecTmp->at(i));
		points->push_back(vecTmp->at(i + 1));
		points->push_back(osg::Vec3(0, 0, 0));
	}

	//�����涥�����λ�ò���
	for (radio += radioStep; radio < radioMax; radio += radioStep)
	{
		double z = radio * radio * value;
		if (radio > radioMax || z > zMax || z < -zMax)
			break;

		vecTmp->clear();
		for (int i = 0; i < samplingNumber + 1; ++i)
			vecTmp->push_back(osg::Vec3(radio * angleSin[i], radio * angleCos[i], z));

		//������ת���������ζ���
		for (int i = 0; i < samplingNumber; ++i)
		{
			points->push_back(vecTmp->at(i + 1));
			points->push_back(vecTmp->at(i));
			points->push_back(vecPre->at(i));

			points->push_back(vecPre->at(i));
			points->push_back(vecPre->at(i + 1));
			points->push_back(vecTmp->at(i + 1));
		}

		vecPre->clear();
		vecPre->insert(vecPre->begin(), vecTmp->begin(), vecTmp->end());
	}

	//����ÿ�������εķ�����
	int numPoints = points->size();
	norms->reserve(numPoints);
	for (int i = 0; i < numPoints / 3; ++i)
	{
		const auto& ptA = points->at(i * 3);
		const auto& ptB = points->at(i * 3 + 1);
		const auto& ptC = points->at(i * 3 + 2);

		//��� + ��λ��
		osg::Vec3 norm = (ptA - ptB).operator^ (ptB - ptC);
		norm.normalize();
		norms->push_back(norm);
		norms->push_back(norm);
		norms->push_back(norm);
	}
	return true;
}