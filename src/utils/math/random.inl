namespace WW::Math
{

template <typename RandomEngine>
template <typename... Args>
RandomGenerator<RandomEngine>::RandomGenerator(Args&&... args)
    : engine_(std::forward<Args>(args)...)
{
}

template <typename RandomEngine>
template <typename... Args>
void RandomGenerator<RandomEngine>::Seed(Args &&... args)
{
    engine_.seed(std::forward<Args>(args)...);
}

template <typename RandomEngine>
template <
    typename DistributionType,
    typename... Args
> typename DistributionType::result_type RandomGenerator<RandomEngine>::Distribution(Args &&... args)
{
    DistributionType dist(std::forward<Args>(args)...);
    return dist(engine_);
}

template <typename RandomEngine>
bool RandomGenerator<RandomEngine>::BernoulliDistribution(double p)
{
    return Distribution<std::bernoulli_distribution>(p);
}

template <typename RandomEngine>
float RandomGenerator<RandomEngine>::NormalDistribution(float mean, float stddev)
{
    return Distribution<std::normal_distribution<float>>(mean, stddev);
}

template <typename RandomEngine>
template <typename NumberType>
NumberType RandomGenerator<RandomEngine>::UniformDistribution(NumberType min, NumberType max)
{
    return Distribution<typename UniformDistribution_t<NumberType>>(min, max);
}

template <
    typename DistributionType,
    typename RandomEngine
>
template <
    typename SeedType,
    typename... Args
> DistributionRandomGenerator<DistributionType, RandomEngine>::DistributionRandomGenerator(SeedType && seed, Args &&... args)
    : dist_(std::forward<Args>(args)...)
    , engine_(seed)
{
}

template <
    typename DistributionType,
    typename RandomEngine
>
template <typename... Args>
void DistributionRandomGenerator<DistributionType, RandomEngine>::Seed(Args &&... args)
{
    engine_.seed(std::forward<Args>(args)...);
}

template <
    typename DistributionType,
    typename RandomEngine
>
typename DistributionType::result_type DistributionRandomGenerator<DistributionType, RandomEngine>::Generate()
{
    return dist_(engine_);
}

} // namespace WW::Math
